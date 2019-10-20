

/**
 * Tencent is pleased to support the open source community by making Tseer available.
 *
 * Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
 *
 * Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
 * in compliance with the License. You may obtain a copy of the License at
 *
 * https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software distributed
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License.
 */
#include "servant/Application.h"
#include "RouterHttpImp.h"
#include "RollLogger.h"
#include "ApiRouterFactory.h"

using namespace Tseer;


void RouterHttpImp::initialize()
{
	_supportMethods["getRouterNode"]	= &RouterHttpImp::getRouterNode;
	_supportMethods["reportStat"]		= &RouterHttpImp::reportStat;
}


void RouterHttpImp::destroy()
{
}

int RouterHttpImp::doRequest( tars::TarsCurrentPtr current, vector < char > &response )
{
	int	ret = -1;
	string		errMsg;
	do
	{
		__TRY__ const vector < char > &request = current->getRequestBuffer();

		tars::TC_HttpRequest httpRequest;
		httpRequest.decode( (const char *) &request[0], request.size() );

		if (!httpRequest.isPOST() )
		{
			errMsg	= "only support get/post method";
			ret	= -2;
			break;
		}

		string method = TC_Common::trim(httpRequest.getRequestUrl(),"/");
		TLOGDEBUG(FILE_FUN << "method:" << method << endl);

		/* 检查method名字是否合法 */
		std::map < string, CommandHandler >::const_iterator it = _supportMethods.find( method );

		if ( it == _supportMethods.end() )
		{
			errMsg	= "not support such API:" + method;
			ret	= -3;
			break;
		}

		string httpBody = httpRequest.getContent();

		rapidjson::Document	document;
		rapidjson::ParseResult	bParseOk = document.Parse( httpBody.c_str() );

		/*
		 * 某些获取接口不需要传请求参数进来，
		 * 此时rapidjson解析时会认为失败，所以要做非空判断避免这种逻辑
		 */
		if ( !bParseOk && !httpBody.empty() )
		{
			errMsg	= "invalid json params";
			ret	= -4;
			TLOGDEBUG(FILE_FUN <<method <<"|"<< httpBody<< "|parse json error" << endl);
			break;
		}

		/**
		map < string, string > context;
		context.insert( make_pair( "method", method ) );
		current->setResponseContext( context );
		**/
		//调用对应的方法
		(this->*(it->second) )( current, document );
		return(0);

		__CATCHEXT__
	}
	while ( 0 );

	TLOGERROR(FILE_FUN << current->getIp() << ":" << current->getPort() << "|" << errMsg << "|" << ret << endl);

	if ( current->isResponse() )
	{
		doResponse( current, int(ret), errMsg );
	}


	return(0);
}


/*
struct AgentRouterRequest
{
	1 optional LB_GET_TYPE				getType;		//获取方式，必填
	2 optional LB_TYPE					lbType; 		//负载均衡方式，按照需要填写
	3 optional string					obj;			//请求服务路由名称，必填
	4 optional string					setname;		//set信息，当按照SET方式获取时必填
	6 optional string					apiVer; 		//API的版本号的版本号，选填
	7 optional long 					hashKey;		//hash key，选择哈希负载均衡时必填
	8 optional string					identifier; 	//进程号，用于区分客户端,必填
};
HttpBody为对应的json格式
curl "http://127.0.0.1:8965/getRouterNode" -d "{\"obj\":\"TSeer.access\",\"identifier\":\"php\",\"lbType\":\"LB_TYPE_ALL\",\"getType\":\"GET_ALL\"}"


*/
int RouterHttpImp::getRouterNode( TarsCurrentPtr current, rapidjson::Document & jData )
{
	TLOGDEBUG(FILE_FUN<<",begin to handle" << endl);
	int64_t hashKey = -1;
	string getType,lbType,obj,setname,apiVer,identifier;
	int ret = -1;
	string errMsg;
	rapidjson::Document rsp_doc;
	rsp_doc.SetObject();
	do{
		if (jData.HasMember("getType") && jData["getType"].IsString())
		{
			getType = jData["getType"].GetString();
		}
		if (jData.HasMember("lbType") && jData["lbType"].IsString())
		{
			lbType = jData["lbType"].GetString();
		}
		if (jData.HasMember("obj") && jData["obj"].IsString())
		{
			obj = jData["obj"].GetString();
		}
		if (jData.HasMember("setname") && jData["setname"].IsString())
		{
			setname = jData["setname"].GetString();
		}
		if (jData.HasMember("apiVer") && jData["apiVer"].IsString())
		{
			apiVer = jData["apiVer"].GetString();
		}
		if (jData.HasMember("hashKey") && jData["hashKey"].IsInt64())
		{
			hashKey = jData["hashKey"].GetInt();
		}
		if (jData.HasMember("identifier") && jData["identifier"].IsString())
		{
			identifier = jData["identifier"].GetString();
		}
		if(obj.empty() || identifier.empty())
		{
			ret = -1;
			errMsg = "obj or identifier is empty";
			break;
		}
		//按hashKey负载均衡时，hashKey不能为空
		LB_TYPE  eLbType;
		stoe(lbType,eLbType);
		if(eLbType== LB_TYPE::LB_TYPE_CST_HASH && hashKey == -1)
		{
			ret = -2;
			errMsg = "hashKey can not be empty";
			break;
		}

		LB_GET_TYPE  eGetTYPE;
		
		stoe(getType,eGetTYPE);

		Tseer::AgentRouterRequest req;
		req.getType = eGetTYPE;
		req.lbType = eLbType;
		req.obj = obj;
		req.setname = setname;
		req.apiVer = apiVer;
		req.hashKey = hashKey;
		req.identifier = identifier;
		
		Tseer::AgentRouterResponse rsp;
		
		
		ApiRouterManager*  apiRouter = ApiRouterFactory::getInstance()->getRouterMr(req);
		
        if(apiRouter)
        {
            ret = apiRouter->getRouter(req,rsp,errMsg);
			/**
			//服务节点信息
		    struct RouterNodeInfo
		    {
		      1 optional string ip;		    //服务ip地址
		      2 optional int  	port;		//端口
		      3 optional bool   isTcp;		//是否使用TCP，否则为UDP
		      4 optional int    weight;	    //静态权重
			  5 optional string setname;    //set信息，只当节点开启了set才有
		    };
			
			//从Agent获取服务节点的数据结构
			struct AgentRouterResponse
			{
				1 optional LB_GET_TYPE				getType;					//获取方式（已废弃）
				2 optional string					obj;						//服务路由名称
				3 optional string					setname;						//set信息
				4 optional vector<RouterNodeInfo>	resultList;					//服务节点信息
			};
			**/
			//拼装json

			rapidjson::Document::AllocatorType &allocator=rsp_doc.GetAllocator();
			rsp_doc.AddMember("ret",ret,allocator);
			string tmp_getType = etos(rsp.getType);
			rapidjson::Value getTypeJson(tmp_getType.c_str(), allocator);
			rsp_doc.AddMember("getType",getTypeJson,allocator);

			rapidjson::Value objJson(rsp.obj.c_str(), allocator);
			rsp_doc.AddMember("obj",objJson,allocator);

			rapidjson::Value setnameJson(rsp.setname.c_str(), allocator);
			rsp_doc.AddMember("setname",setnameJson,allocator);

			rapidjson::Value array1(rapidjson::kArrayType);
			for(size_t i = 0;i<rsp.resultList.size();i++)
			{
				rapidjson::Value  item_obj(rapidjson::kObjectType);

				rapidjson::Value ipJson(rsp.resultList[i].ip.c_str(), allocator);
				item_obj.AddMember("ip",ipJson,allocator);
				
				item_obj.AddMember("port",rsp.resultList[i].port,allocator);
				item_obj.AddMember("isTcp",rsp.resultList[i].isTcp,allocator);
				item_obj.AddMember("weight",rsp.resultList[i].weight,allocator);
				rapidjson::Value setnameJson(rsp.resultList[i].setname.c_str(), allocator);				
				item_obj.AddMember("setname",setnameJson,allocator);

				array1.PushBack(item_obj,allocator);
			}
			rsp_doc.AddMember("resultList",array1,allocator); 
			/*
			rapidjson::StringBuffer strBuf;
			rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
			json_obj.Accept(writer);
			
    		string data = strBuf.GetString();//json结构
    		*/
 			
			
        }
        else
        {
            errMsg = "get apiRouter null";
            ret = -3;
            break;
        }

	}while(0);
	doResponse(current,ret,rsp_doc, errMsg);	
	return(0);
}


/*
//上报调用状态的数据结构
struct NodeStat {
	1 optional string					localIp;			//本机ip
	2 optional int						timeCost;			//调用耗时
	3 optional int						ret;				//调用返回错误码
	4 optional string					moduleName; 		//主调模块名称
	5 optional string					ip; 				//被调服务ip
	6 optional int						port;				//被调服务port
	7 optional string					obj;				//被调服务路由名称
	8 optional bool 					isTcp;				//是否使用TCP，false为UDP
	9 optional string					setname;			//set信息
	10 optional string					apiVer; 			//API的版本号的版本号，选填
	11 optional LB_TYPE 				lbType; 			//负载均衡方式
	12 optional LB_GET_TYPE 			getType;			//获取方式
	13 optional string					identifier; 		//进程号，用于区分客户端
};

*/
int RouterHttpImp::reportStat( TarsCurrentPtr current, rapidjson::Document & jData )
{
	
	current->setResponse(false);

	TLOGDEBUG(FILE_FUN<<",begin to handle" << endl);
	NodeStat stat;

	if (jData.HasMember("localIp") && jData["localIp"].IsString())
	{
		stat.localIp = jData["localIp"].GetString();
	}
	if (jData.HasMember("timeCost") && jData["timeCost"].IsInt())
	{
		stat.timeCost = jData["timeCost"].GetInt();
	}
	if (jData.HasMember("ret") && jData["ret"].IsInt())
	{
		stat.ret = jData["ret"].GetInt();
	}
	if (jData.HasMember("moduleName") && jData["moduleName"].IsString())
	{
		stat.moduleName = jData["moduleName"].GetString();
	}
	if (jData.HasMember("ip") && jData["ip"].IsString())
	{
		stat.ip = jData["ip"].GetString();
	}
	if (jData.HasMember("port") && jData["port"].IsInt())
	{
		stat.port = jData["port"].GetInt();
	}
	if (jData.HasMember("obj") && jData["obj"].IsString())
	{
		stat.obj = jData["obj"].GetString();
	}
	if (jData.HasMember("isTcp") && jData["isTcp"].IsInt())
	{
		stat.isTcp = jData["isTcp"].GetInt();
	}
	if (jData.HasMember("setname") && jData["setname"].IsString())
	{
		stat.setname = jData["setname"].GetString();
	}

	if (jData.HasMember("apiVer") && jData["apiVer"].IsString())
	{
		stat.apiVer = jData["apiVer"].GetString();
	}
	if (jData.HasMember("lbType") && jData["lbType"].IsString())
	{
		stoe(jData["lbType"].GetString(),stat.lbType);
	}
	if (jData.HasMember("getType") && jData["getType"].IsString())
	{
		stoe(jData["getType"].GetString(),stat.getType);
	}
	if (jData.HasMember("identifier") && jData["identifier"].IsString())
	{
		stat.identifier = jData["identifier"].GetString();
	}

	//检查参数
	if (stat.obj.empty())
	{
	    ostringstream msgBuffer;
	    msgBuffer << FILE_FUN << "empty obj";
	    return -1;
	}

	    Tseer::AgentRouterRequest req;
	    req.identifier = stat.identifier;
	    req.getType = stat.getType;
	    req.lbType = stat.lbType;
	    req.obj = stat.obj;
	    req.setname = stat.setname;
	    
	    int ret = 0;
	    string errMsg;
	    ApiRouterManager*  apiRouter = ApiRouterFactory::getInstance()->getRouterMr(req);
	    if(apiRouter)
	    {
	        Tseer::RouterNodeInfo nodeInfo;
	        nodeInfo.ip = stat.ip;
	        nodeInfo.port = stat.port;
	        nodeInfo.isTcp = stat.isTcp;
	        //更新nodeInfo 对应的调用统计信息，用来作为负载均衡和超时屏蔽依据
	        ret = apiRouter->updateStat(req,nodeInfo,stat.ret,stat.timeCost,errMsg);
	    }
	    else
	    {
	        errMsg = "get apiRouter null";
	        ret = GET_ROUTER_INNER_ERR;
	    }
	    
	    TSEER_LOG(COMMON_LOG)->debug() << FILE_FUN
	        <<"obj:" << req.obj << "|" << Tseer::etos(req.getType) 
	        <<"|"<< Tseer::etos(req.lbType)
	        <<"|set:" << req.setname
	        <<"|identifer:"<<req.identifier
	        <<"|ret:"<<ret
	        <<"|errmsg:"<<errMsg
	        <<endl;

	    return ret;

	return(0);
}


void RouterHttpImp::doResponse(TarsCurrentPtr current, int ret, rapidjson::Document &document, const string& errMsg)
{
    __TRY__

    TC_HttpResponse  response;
    
    rapidjson::Document::AllocatorType &allocator = document.GetAllocator();

    TC_Endpoint endpoint = current->getBindAdapter()->getEndpoint();
    string callChain = endpoint.getHost() + TC_Common::tostr(endpoint.getPort());
    rapidjson::Value callChainJson(callChain.c_str(), allocator);
    rapidjson::Value errMsgJson(errMsg.c_str(), allocator);
    
    document.AddMember("call_chain", callChainJson, allocator);
    document.AddMember("err_msg", errMsgJson, allocator);
    document.AddMember("ret_code", ret, allocator);

    rapidjson::StringBuffer sb;
    rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
    document.Accept(writer);
    string responseContent = sb.GetString();
    string method;
    map<string, string>::const_iterator itMethod = current->getResponseContext().find("method");
    if (itMethod != current->getResponseContext().end())
        method = itMethod->second;
	TLOGDEBUG(FILE_FUN << method<<"|responseContent=" << responseContent << endl);
    
    response.setResponse(responseContent.c_str(),responseContent.size());
    current->sendResponse(response.encode().c_str(),response.encode().size());
    __CATCH__
}

void RouterHttpImp::doResponse(TarsCurrentPtr current, int ret,const string& errMsg)
{
    __TRY__

    TC_HttpResponse  response;

    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType &allocator = document.GetAllocator();
    
#if 0
    string callChain = current->getBindAdapter()->getEndpoint().getHost() + ":" + TC_Common::tostr(current->getBindAdapter()->getEndpoint().getPort());
#else
    TC_Endpoint endpoint = current->getBindAdapter()->getEndpoint();
    string callChain = endpoint.getHost() + TC_Common::tostr(endpoint.getPort());
#endif
    rapidjson::Value callChainJson(callChain.c_str(), allocator);
    rapidjson::Value errMsgJson(errMsg.c_str(), allocator);
    document.AddMember("call_chain", callChainJson, allocator);
    document.AddMember("err_msg", errMsgJson, allocator);
    document.AddMember("ret_code", ret, allocator);

    rapidjson::Value resultData(rapidjson::kArrayType);
    document.AddMember("data", resultData, allocator);
    
    rapidjson::StringBuffer sb;
    rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
    document.Accept(writer);
    
    string responseContent = sb.GetString();
    string method;
    map<string, string>::const_iterator itMethod = current->getResponseContext().find("method");
    if (itMethod != current->getResponseContext().end())
        method = itMethod->second;

	
	TLOGDEBUG(FILE_FUN<<method<<"|responseContent=" << responseContent << endl);
    response.setResponse(responseContent.c_str(),responseContent.size());
    current->sendResponse(response.encode().c_str(),response.encode().size());
    __CATCH__
}



