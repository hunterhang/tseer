<?php
//1 optional stringlocalIp;optional//本机ip
//2 optional inttimeCost;optional//调用耗时
//3 optional intret;调用耗时//调用返回错误码
//4 optional stringmoduleName;		//主调模块名称
//5 optional stringmoduleNameip;				//被调服务ip
//6 optional inttimeCostport;ip//被调服务port
//	7 optional stringobj;port//被调服务路由名称
//	8 optional bool						isTcp;optional//是否使用TCP，false为UDP
//	9 optional stringsetname;optional//set信息
//	10 optional stringlocalIpapiVer;			//API的版本号的版本号，选填
//11 optional LB_TYPE					lbType;				//负载均衡方式
//12 optional LB_GET_TYPE				getType;LB_GET_TYPE//获取方式
//	13 optional stringmoduleNameidentifier;			//进程号，用于区分客户端

class TseerClient{
	private $_socket1 = -1;//GetNodeSocket
	private $_socket2 = -2;//ReportStatSocket
	private $_ip = "127.0.0.1";
	private $_port = "8965";
	public function Init(){
		$this->Conn($this->_socket1);
		$this->Conn($this->_socket2);
		return 0;
	}
	/**
	 * 获取调用的IP，PORT
	 */
	public function GetRouterNode($obj,$identifier,$lbType,$getType)
	{
		$arr = array(
			"obj"=>$obj,
			"identifier"=>$identifier,
			"lbType"=>$lbType,
			"getType"=>$getType
		);	
		$body = json_encode($arr);
		$body_len = strlen($body);
		$url = "/getRouterNode";
		if($this->SendHttp($this->_socket1,$url,$body,$rsp,true) != 0)
		{
			return -1;
		}
		return 0;
	}
	/**
	 *上报调用状态的数据结构
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
	public function ReportStat($data)
	{
		$body = json_encode($data);
		$url = "/reportStat";
		$rsp = "";
		if($this->SendHttp($this->_socket2,$url,$body,$rsp,false) != 0)
		{
			return -1;
		}
		return 0;

	}
	private function SendHttp(&$socket,$url,$body,&$rsp,$is_rsp)
	{
		$body_len = strlen($body);
		$buf = <<<EOF
POST $url Http/1.1\r\nHost: $this->_ip:$this->_port\r\nContent-Length: $body_len\r\n\r\n$body
EOF;
		if(socket_write($socket,$buf,strlen($buf)) == false)
		{
			echo "socket_write fail!";
			socket_close($socket);
			$socket = -1;
			return -1;
		}
		if($is_rsp == false)
		{
			return 0;
		}
		$except_rev_len = 1024;
		$rsp_buf = "";
		do{
			$buf = socket_read($socket,$except_rev_len);
			$rsp_buf .= $buf;
			if(strlen($buf) <= $except_rev_len)
			{
				break;
			}
		}while(1);
		$arr = explode("\r\n\r\n",$rsp_buf);
		$rsp = $arr[1];
		return 0;
	}
	private function Conn(&$socket){
		$socket = socket_create(AF_INET,SOCK_STREAM,SOL_TCP);
		/****************设置socket连接选项，这两个步骤你可以省略*************/
		//接收套接流的最大超时时间1秒，后面是微秒单位超时时间，设置为零，表示不管它
		socket_set_option($socket, SOL_SOCKET, SO_RCVTIMEO, array("sec" => 1, "usec" => 0));
		//发送套接流的最大超时时间为6秒
		socket_set_option($socket, SOL_SOCKET, SO_SNDTIMEO, array("sec" => 6, "usec" => 0));
		/****************设置socket连接选项，这两个步骤你可以省略*************/

		//连接服务端的套接流，这一步就是使客户端与服务器端的套接流建立联系
		if(socket_connect($socket,$this->_ip,$this->_port) == false){
			echo 'connect fail massege:'.socket_strerror(socket_last_error());
			socket_close($socket);
			$socket = -1;
			return -1;
		}
		return 0;
	}
}
//curl "http://127.0.0.1:8965/getRouterNode" -d "{\"obj\":\"HSB.YouPin.User.Auth\",\"identifier\":\"php\",\"lbType\":\"LB_TYPE_ALL\",\"getType\":\"GET_ALL\"}"
/**
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
	//获取方式
	enum LB_GET_TYPE
	{
		GET_IDC,				//按IDC
		GET_SET,				//按set
		GET_ALL,				//全部获取
	};
	
	enum LB_TYPE
	{
		LB_TYPE_LOOP,
		LB_TYPE_RANDOM,
		LB_TYPE_STATIC_WEIGHT,
		LB_TYPE_CST_HASH,
		LB_TYPE_ALL
	};
*/
$client = new TseerClient();
$client->Init();

$data = array(
	"localIp"=>"127.0.0.1",
	"timeCost"=>30,
	"ret"=>0,
	"moduleName"=>"HSB.YouPin.User.Access",
	"ip"=>"127.0.0.1",
	"port"=>10086,
	"obj"=>"HSB.YouPin.User.Auth",
	"isTcp"=>true,
	"lbType"=>"GET_IDC",
	"getType"=>"LB_TYPE_ALL",
	"identifier"=>"php"
);
echo microtime();
list($usec1, $sec1) = explode(" ", microtime());
for($i=0;$i<10000;$i++)
{
	$ret = $client->GetRouterNode("HSB.YouPin.User.Auth","php","LB_TYPE_ALL","GET_ALL");
	if($ret != 0)
	{
		echo "Get Error\n";
		break;
	}
	$ret = $client->ReportStat($data);
	if($ret != 0)
	{
		echo "Get Error1\n";
		break;
	}
	if($i%1000 == 0)
	{
		echo $i."\n";
	}
}
list($usec2, $sec2) = explode(" ", microtime());
$total_time = (($usec2  + $sec2* 1000000) - ($usec1 + $sec1* 1000000))/1000;
$argv_time =$total_time/($i+1)/1000;
echo "平时时间：".$argv_time." ms,总时长：$total_time ms\n";
echo microtime()."\n";
