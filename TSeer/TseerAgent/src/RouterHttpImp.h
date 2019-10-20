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

#ifndef __AGENT_ROUTER_HTTP_IMP_H_
#define __AGENT_ROUTER_HTTP_IMP_H_

#include "TseerAgent.h"
#include "util/tc_http.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"

#define __TRY__        try{
#define __CATCH__    }catch(exception& ex) \
    { \
        TLOGERROR(FILE_FUN << "exception: " << ex.what() << endl); \
    } \
    catch(...) \
    { \
        TLOGERROR(FILE_FUN << "unknown exception" << endl); \
    }

#define __CATCHEXT__    }catch(exception& ex) \
    { \
        errMsg += string(ex.what());\
        TLOGERROR(FILE_FUN << "exception: " << ex.what() << endl); \
    } \
    catch(...) \
    { \
        errMsg += "unknown exception";\
        TLOGERROR(FILE_FUN << "unknown exception" << endl); \
    }


class RouterHttpImp : public tars::Servant
{
public:
    
    virtual ~RouterHttpImp() {}

    virtual void initialize();

    virtual void destroy();

    virtual int doRequest(tars::TarsCurrentPtr current, vector<char>& response);

	virtual void doResponse(TarsCurrentPtr current, int ret, rapidjson::Document &document, const string& errMsg);
	virtual void doResponse(TarsCurrentPtr current, int ret,const string& errMsg);

private:
	//获取IP列表
	int getRouterNode(TarsCurrentPtr current, rapidjson::Document &jData);
	//上报数据
	int reportStat(TarsCurrentPtr current, rapidjson::Document &jData);
   //支持的API名称 
   typedef int (RouterHttpImp::*CommandHandler)(TarsCurrentPtr, rapidjson::Document& );
   std::map<string, CommandHandler> _supportMethods;
   
    enum GET_ROUTER_RET
    {
        GET_ROUTER_SUCCESS = 0,              //成功
        GET_ROUTER_NOT_EXIST = -1,             //服务不存在（常因Obj名字错误或服务已经下线引起）
        GET_ROUTER_FAILED = -2,             //失败
        GET_ROUTER_INNER_ERR = -3,             //内部错误
        GET_ROUTER_PARAM_ERR = -4             //入参错误

    };
};

#endif
