// **********************************************************************
// This file was generated by a TARS parser!
// TARS version 1.1.0.
// **********************************************************************

#ifndef __TSEERAGENT_H_
#define __TSEERAGENT_H_

#include <map>
#include <string>
#include <vector>
#include "tup/Tars.h"
using namespace std;
#include "TseerAgentComm.h"
#include "servant/ServantProxy.h"
#include "servant/Servant.h"
#include "promise/promise.h"


namespace Tseer
{

    /* callback of async proxy for client */
    class RouterPrxCallback: public tars::ServantProxyCallback
    {
    public:
        virtual ~RouterPrxCallback(){}
        virtual void callback_getRouterNode(tars::Int32 ret,  const Tseer::AgentRouterResponse& rsp)
        { throw std::runtime_error("callback_getRouterNode() override incorrect."); }
        virtual void callback_getRouterNode_exception(tars::Int32 ret)
        { throw std::runtime_error("callback_getRouterNode_exception() override incorrect."); }

        virtual void callback_reportStat(tars::Int32 ret)
        { throw std::runtime_error("callback_reportStat() override incorrect."); }
        virtual void callback_reportStat_exception(tars::Int32 ret)
        { throw std::runtime_error("callback_reportStat_exception() override incorrect."); }

    public:
        virtual const map<std::string, std::string> & getResponseContext() const
        {
            CallbackThreadData * pCbtd = CallbackThreadData::getData();
            assert(pCbtd != NULL);

            if(!pCbtd->getContextValid())
            {
                throw TC_Exception("cann't get response context");
            }
            return pCbtd->getResponseContext();
        }

    public:
        virtual int onDispatch(tars::ReqMessagePtr msg)
        {
            static ::std::string __Router_all[]=
            {
                "getRouterNode",
                "reportStat"
            };
            pair<string*, string*> r = equal_range(__Router_all, __Router_all+2, string(msg->request.sFuncName));
            if(r.first == r.second) return tars::TARSSERVERNOFUNCERR;
            switch(r.first - __Router_all)
            {
                case 0:
                {
                    if (msg->response.iRet != tars::TARSSERVERSUCCESS)
                    {
                        callback_getRouterNode_exception(msg->response.iRet);

                        return msg->response.iRet;
                    }
                    tars::TarsInputStream<tars::BufferReader> _is;

                    _is.setBuffer(msg->response.sBuffer);
                    tars::Int32 _ret;
                    _is.read(_ret, 0, true);

                    Tseer::AgentRouterResponse rsp;
                    _is.read(rsp, 2, true);
                    CallbackThreadData * pCbtd = CallbackThreadData::getData();
                    assert(pCbtd != NULL);

                    pCbtd->setResponseContext(msg->response.context);

                    callback_getRouterNode(_ret, rsp);

                    pCbtd->delResponseContext();

                    return tars::TARSSERVERSUCCESS;

                }
                case 1:
                {
                    if (msg->response.iRet != tars::TARSSERVERSUCCESS)
                    {
                        callback_reportStat_exception(msg->response.iRet);

                        return msg->response.iRet;
                    }
                    tars::TarsInputStream<tars::BufferReader> _is;

                    _is.setBuffer(msg->response.sBuffer);
                    tars::Int32 _ret;
                    _is.read(_ret, 0, true);

                    CallbackThreadData * pCbtd = CallbackThreadData::getData();
                    assert(pCbtd != NULL);

                    pCbtd->setResponseContext(msg->response.context);

                    callback_reportStat(_ret);

                    pCbtd->delResponseContext();

                    return tars::TARSSERVERSUCCESS;

                }
            }
            return tars::TARSSERVERNOFUNCERR;
        }

    };
    typedef tars::TC_AutoPtr<RouterPrxCallback> RouterPrxCallbackPtr;

    /* callback of promise async proxy for client */
    class RouterPrxCallbackPromise: public tars::ServantProxyCallback
    {
    public:
        virtual ~RouterPrxCallbackPromise(){}
    public:
        struct PromisegetRouterNode: virtual public TC_HandleBase
        {
        public:
            tars::Int32 _ret;
            Tseer::AgentRouterResponse rsp;
            map<std::string, std::string> _mRspContext;
        };
        
        typedef tars::TC_AutoPtr< RouterPrxCallbackPromise::PromisegetRouterNode > PromisegetRouterNodePtr;

        RouterPrxCallbackPromise(const promise::Promise< RouterPrxCallbackPromise::PromisegetRouterNodePtr > &promise)
        : _promise_getRouterNode(promise)
        {}
        
        virtual void callback_getRouterNode(const RouterPrxCallbackPromise::PromisegetRouterNodePtr &ptr)
        {
            _promise_getRouterNode.setValue(ptr);
        }
        virtual void callback_getRouterNode_exception(tars::Int32 ret)
        {
            std::string str("");
            str += "Function:getRouterNode_exception|Ret:";
            str += TC_Common::tostr(ret);
            _promise_getRouterNode.setException(promise::copyException(str, ret));
        }

    protected:
        promise::Promise< RouterPrxCallbackPromise::PromisegetRouterNodePtr > _promise_getRouterNode;

    public:
        struct PromisereportStat: virtual public TC_HandleBase
        {
        public:
            tars::Int32 _ret;
            map<std::string, std::string> _mRspContext;
        };
        
        typedef tars::TC_AutoPtr< RouterPrxCallbackPromise::PromisereportStat > PromisereportStatPtr;

        RouterPrxCallbackPromise(const promise::Promise< RouterPrxCallbackPromise::PromisereportStatPtr > &promise)
        : _promise_reportStat(promise)
        {}
        
        virtual void callback_reportStat(const RouterPrxCallbackPromise::PromisereportStatPtr &ptr)
        {
            _promise_reportStat.setValue(ptr);
        }
        virtual void callback_reportStat_exception(tars::Int32 ret)
        {
            std::string str("");
            str += "Function:reportStat_exception|Ret:";
            str += TC_Common::tostr(ret);
            _promise_reportStat.setException(promise::copyException(str, ret));
        }

    protected:
        promise::Promise< RouterPrxCallbackPromise::PromisereportStatPtr > _promise_reportStat;

    public:
        virtual int onDispatch(tars::ReqMessagePtr msg)
        {
            static ::std::string __Router_all[]=
            {
                "getRouterNode",
                "reportStat"
            };

            pair<string*, string*> r = equal_range(__Router_all, __Router_all+2, string(msg->request.sFuncName));
            if(r.first == r.second) return tars::TARSSERVERNOFUNCERR;
            switch(r.first - __Router_all)
            {
                case 0:
                {
                    if (msg->response.iRet != tars::TARSSERVERSUCCESS)
                    {
                        callback_getRouterNode_exception(msg->response.iRet);

                        return msg->response.iRet;
                    }
                    tars::TarsInputStream<tars::BufferReader> _is;

                    _is.setBuffer(msg->response.sBuffer);

                    RouterPrxCallbackPromise::PromisegetRouterNodePtr ptr = new RouterPrxCallbackPromise::PromisegetRouterNode();

                    try
                    {
                        _is.read(ptr->_ret, 0, true);

                        _is.read(ptr->rsp, 2, true);
                    }
                    catch(std::exception &ex)
                    {
                        callback_getRouterNode_exception(tars::TARSCLIENTDECODEERR);

                        return tars::TARSCLIENTDECODEERR;
                    }
                    catch(...)
                    {
                        callback_getRouterNode_exception(tars::TARSCLIENTDECODEERR);

                        return tars::TARSCLIENTDECODEERR;
                    }

                    ptr->_mRspContext = msg->response.context;

                    callback_getRouterNode(ptr);

                    return tars::TARSSERVERSUCCESS;

                }
                case 1:
                {
                    if (msg->response.iRet != tars::TARSSERVERSUCCESS)
                    {
                        callback_reportStat_exception(msg->response.iRet);

                        return msg->response.iRet;
                    }
                    tars::TarsInputStream<tars::BufferReader> _is;

                    _is.setBuffer(msg->response.sBuffer);

                    RouterPrxCallbackPromise::PromisereportStatPtr ptr = new RouterPrxCallbackPromise::PromisereportStat();

                    try
                    {
                        _is.read(ptr->_ret, 0, true);

                    }
                    catch(std::exception &ex)
                    {
                        callback_reportStat_exception(tars::TARSCLIENTDECODEERR);

                        return tars::TARSCLIENTDECODEERR;
                    }
                    catch(...)
                    {
                        callback_reportStat_exception(tars::TARSCLIENTDECODEERR);

                        return tars::TARSCLIENTDECODEERR;
                    }

                    ptr->_mRspContext = msg->response.context;

                    callback_reportStat(ptr);

                    return tars::TARSSERVERSUCCESS;

                }
            }
            return tars::TARSSERVERNOFUNCERR;
        }

    };
    typedef tars::TC_AutoPtr<RouterPrxCallbackPromise> RouterPrxCallbackPromisePtr;

    /* callback of coroutine async proxy for client */
    class RouterCoroPrxCallback: public RouterPrxCallback
    {
    public:
        virtual ~RouterCoroPrxCallback(){}
    public:
        virtual const map<std::string, std::string> & getResponseContext() const { return _mRspContext; }

        virtual void setResponseContext(const map<std::string, std::string> &mContext) { _mRspContext = mContext; }

    public:
        int onDispatch(tars::ReqMessagePtr msg)
        {
            static ::std::string __Router_all[]=
            {
                "getRouterNode",
                "reportStat"
            };

            pair<string*, string*> r = equal_range(__Router_all, __Router_all+2, string(msg->request.sFuncName));
            if(r.first == r.second) return tars::TARSSERVERNOFUNCERR;
            switch(r.first - __Router_all)
            {
                case 0:
                {
                    if (msg->response.iRet != tars::TARSSERVERSUCCESS)
                    {
                        callback_getRouterNode_exception(msg->response.iRet);

                        return msg->response.iRet;
                    }
                    tars::TarsInputStream<tars::BufferReader> _is;

                    _is.setBuffer(msg->response.sBuffer);
                    try
                    {
                        tars::Int32 _ret;
                        _is.read(_ret, 0, true);

                        Tseer::AgentRouterResponse rsp;
                        _is.read(rsp, 2, true);
                        setResponseContext(msg->response.context);

                        callback_getRouterNode(_ret, rsp);

                    }
                    catch(std::exception &ex)
                    {
                        callback_getRouterNode_exception(tars::TARSCLIENTDECODEERR);

                        return tars::TARSCLIENTDECODEERR;
                    }
                    catch(...)
                    {
                        callback_getRouterNode_exception(tars::TARSCLIENTDECODEERR);

                        return tars::TARSCLIENTDECODEERR;
                    }

                    return tars::TARSSERVERSUCCESS;

                }
                case 1:
                {
                    if (msg->response.iRet != tars::TARSSERVERSUCCESS)
                    {
                        callback_reportStat_exception(msg->response.iRet);

                        return msg->response.iRet;
                    }
                    tars::TarsInputStream<tars::BufferReader> _is;

                    _is.setBuffer(msg->response.sBuffer);
                    try
                    {
                        tars::Int32 _ret;
                        _is.read(_ret, 0, true);

                        setResponseContext(msg->response.context);

                        callback_reportStat(_ret);

                    }
                    catch(std::exception &ex)
                    {
                        callback_reportStat_exception(tars::TARSCLIENTDECODEERR);

                        return tars::TARSCLIENTDECODEERR;
                    }
                    catch(...)
                    {
                        callback_reportStat_exception(tars::TARSCLIENTDECODEERR);

                        return tars::TARSCLIENTDECODEERR;
                    }

                    return tars::TARSSERVERSUCCESS;

                }
            }
            return tars::TARSSERVERNOFUNCERR;
        }

    protected:
        map<std::string, std::string> _mRspContext;
    };
    typedef tars::TC_AutoPtr<RouterCoroPrxCallback> RouterCoroPrxCallbackPtr;

    /* proxy for client */
    class RouterProxy : public tars::ServantProxy
    {
    public:
        typedef map<string, string> TARS_CONTEXT;
        tars::Int32 getRouterNode(const Tseer::AgentRouterRequest & req,Tseer::AgentRouterResponse &rsp,const map<string, string> &context = TARS_CONTEXT(),map<string, string> * pResponseContext = NULL)
        {
            tars::TarsOutputStream<tars::BufferWriter> _os;
            _os.write(req, 1);
            _os.write(rsp, 2);
            tars::ResponsePacket rep;
            std::map<string, string> _mStatus;
            tars_invoke(tars::TARSNORMAL,"getRouterNode", _os.getByteBuffer(), context, _mStatus, rep);
            if(pResponseContext)
            {
                *pResponseContext = rep.context;
            }

            tars::TarsInputStream<tars::BufferReader> _is;
            _is.setBuffer(rep.sBuffer);
            tars::Int32 _ret;
            _is.read(_ret, 0, true);
            _is.read(rsp, 2, true);
            return _ret;
        }

        void async_getRouterNode(RouterPrxCallbackPtr callback,const Tseer::AgentRouterRequest &req,const map<string, string>& context = TARS_CONTEXT())
        {
            tars::TarsOutputStream<tars::BufferWriter> _os;
            _os.write(req, 1);
            std::map<string, string> _mStatus;
            tars_invoke_async(tars::TARSNORMAL,"getRouterNode", _os.getByteBuffer(), context, _mStatus, callback);
        }
        
        promise::Future< RouterPrxCallbackPromise::PromisegetRouterNodePtr > promise_async_getRouterNode(const Tseer::AgentRouterRequest &req,const map<string, string>& context)
        {
            promise::Promise< RouterPrxCallbackPromise::PromisegetRouterNodePtr > promise;
            RouterPrxCallbackPromisePtr callback = new RouterPrxCallbackPromise(promise);

            tars::TarsOutputStream<tars::BufferWriter> _os;
            _os.write(req, 1);
            std::map<string, string> _mStatus;
            tars_invoke_async(tars::TARSNORMAL,"getRouterNode", _os.getByteBuffer(), context, _mStatus, callback);

            return promise.getFuture();
        }

        void coro_getRouterNode(RouterCoroPrxCallbackPtr callback,const Tseer::AgentRouterRequest &req,const map<string, string>& context = TARS_CONTEXT())
        {
            tars::TarsOutputStream<tars::BufferWriter> _os;
            _os.write(req, 1);
            std::map<string, string> _mStatus;
            tars_invoke_async(tars::TARSNORMAL,"getRouterNode", _os.getByteBuffer(), context, _mStatus, callback, true);
        }

        tars::Int32 reportStat(const Tseer::NodeStat & stat,const map<string, string> &context = TARS_CONTEXT(),map<string, string> * pResponseContext = NULL)
        {
            tars::TarsOutputStream<tars::BufferWriter> _os;
            _os.write(stat, 1);
            tars::ResponsePacket rep;
            std::map<string, string> _mStatus;
            tars_invoke(tars::TARSNORMAL,"reportStat", _os.getByteBuffer(), context, _mStatus, rep);
            if(pResponseContext)
            {
                *pResponseContext = rep.context;
            }

            tars::TarsInputStream<tars::BufferReader> _is;
            _is.setBuffer(rep.sBuffer);
            tars::Int32 _ret;
            _is.read(_ret, 0, true);
            return _ret;
        }

        void async_reportStat(RouterPrxCallbackPtr callback,const Tseer::NodeStat &stat,const map<string, string>& context = TARS_CONTEXT())
        {
            tars::TarsOutputStream<tars::BufferWriter> _os;
            _os.write(stat, 1);
            std::map<string, string> _mStatus;
            tars_invoke_async(tars::TARSNORMAL,"reportStat", _os.getByteBuffer(), context, _mStatus, callback);
        }
        
        promise::Future< RouterPrxCallbackPromise::PromisereportStatPtr > promise_async_reportStat(const Tseer::NodeStat &stat,const map<string, string>& context)
        {
            promise::Promise< RouterPrxCallbackPromise::PromisereportStatPtr > promise;
            RouterPrxCallbackPromisePtr callback = new RouterPrxCallbackPromise(promise);

            tars::TarsOutputStream<tars::BufferWriter> _os;
            _os.write(stat, 1);
            std::map<string, string> _mStatus;
            tars_invoke_async(tars::TARSNORMAL,"reportStat", _os.getByteBuffer(), context, _mStatus, callback);

            return promise.getFuture();
        }

        void coro_reportStat(RouterCoroPrxCallbackPtr callback,const Tseer::NodeStat &stat,const map<string, string>& context = TARS_CONTEXT())
        {
            tars::TarsOutputStream<tars::BufferWriter> _os;
            _os.write(stat, 1);
            std::map<string, string> _mStatus;
            tars_invoke_async(tars::TARSNORMAL,"reportStat", _os.getByteBuffer(), context, _mStatus, callback, true);
        }

        RouterProxy* tars_hash(int64_t key)
        {
            return (RouterProxy*)ServantProxy::tars_hash(key);
        }

        RouterProxy* tars_consistent_hash(int64_t key)
        {
            return (RouterProxy*)ServantProxy::tars_consistent_hash(key);
        }

        RouterProxy* tars_set_timeout(int msecond)
        {
            return (RouterProxy*)ServantProxy::tars_set_timeout(msecond);
        }

    };
    typedef tars::TC_AutoPtr<RouterProxy> RouterPrx;

    /* servant for server */
    class Router : public tars::Servant
    {
    public:
        virtual ~Router(){}
        virtual tars::Int32 getRouterNode(const Tseer::AgentRouterRequest & req,Tseer::AgentRouterResponse &rsp,tars::TarsCurrentPtr current) = 0;
        static void async_response_getRouterNode(tars::TarsCurrentPtr current, tars::Int32 _ret, const Tseer::AgentRouterResponse &rsp)
        {
            if (current->getRequestVersion() == TUPVERSION )
            {
                UniAttribute<tars::BufferWriter, tars::BufferReader>  tarsAttr;
                tarsAttr.setVersion(current->getRequestVersion());
                tarsAttr.put("", _ret);
                tarsAttr.put("rsp", rsp);

                vector<char> sTupResponseBuffer;
                tarsAttr.encode(sTupResponseBuffer);
                current->sendResponse(tars::TARSSERVERSUCCESS, sTupResponseBuffer);
            }
            else
            {
                tars::TarsOutputStream<tars::BufferWriter> _os;
                _os.write(_ret, 0);

                _os.write(rsp, 2);

                current->sendResponse(tars::TARSSERVERSUCCESS, _os.getByteBuffer());
            }
        }

        virtual tars::Int32 reportStat(const Tseer::NodeStat & stat,tars::TarsCurrentPtr current) = 0;
        static void async_response_reportStat(tars::TarsCurrentPtr current, tars::Int32 _ret)
        {
            if (current->getRequestVersion() == TUPVERSION )
            {
                UniAttribute<tars::BufferWriter, tars::BufferReader>  tarsAttr;
                tarsAttr.setVersion(current->getRequestVersion());
                tarsAttr.put("", _ret);

                vector<char> sTupResponseBuffer;
                tarsAttr.encode(sTupResponseBuffer);
                current->sendResponse(tars::TARSSERVERSUCCESS, sTupResponseBuffer);
            }
            else
            {
                tars::TarsOutputStream<tars::BufferWriter> _os;
                _os.write(_ret, 0);

                current->sendResponse(tars::TARSSERVERSUCCESS, _os.getByteBuffer());
            }
        }

    public:
        int onDispatch(tars::TarsCurrentPtr _current, vector<char> &_sResponseBuffer)
        {
            static ::std::string __Tseer__Router_all[]=
            {
                "getRouterNode",
                "reportStat"
            };

            pair<string*, string*> r = equal_range(__Tseer__Router_all, __Tseer__Router_all+2, _current->getFuncName());
            if(r.first == r.second) return tars::TARSSERVERNOFUNCERR;
            switch(r.first - __Tseer__Router_all)
            {
                case 0:
                {
                    tars::TarsInputStream<tars::BufferReader> _is;
                    _is.setBuffer(_current->getRequestBuffer());
                    Tseer::AgentRouterRequest req;
                    Tseer::AgentRouterResponse rsp;
                    if (_current->getRequestVersion() == TUPVERSION)
                    {
                        UniAttribute<tars::BufferWriter, tars::BufferReader>  tarsAttr;
                        tarsAttr.setVersion(_current->getRequestVersion());
                        tarsAttr.decode(_current->getRequestBuffer());
                        tarsAttr.get("req", req);
                        tarsAttr.getByDefault("rsp", rsp, rsp);
                    }
                    else
                    {
                        _is.read(req, 1, true);
                        _is.read(rsp, 2, false);
                    }
                    tars::Int32 _ret = getRouterNode(req,rsp, _current);
                    if(_current->isResponse())
                    {
                        if (_current->getRequestVersion() == TUPVERSION )
                        {
                            UniAttribute<tars::BufferWriter, tars::BufferReader>  tarsAttr;
                            tarsAttr.setVersion(_current->getRequestVersion());
                            tarsAttr.put("", _ret);
                            tarsAttr.put("rsp", rsp);
                            tarsAttr.encode(_sResponseBuffer);
                        }
                        else
                        {
                            tars::TarsOutputStream<tars::BufferWriter> _os;
                            _os.write(_ret, 0);
                            _os.write(rsp, 2);
                            _os.swap(_sResponseBuffer);
                        }
                    }
                    return tars::TARSSERVERSUCCESS;

                }
                case 1:
                {
                    tars::TarsInputStream<tars::BufferReader> _is;
                    _is.setBuffer(_current->getRequestBuffer());
                    Tseer::NodeStat stat;
                    if (_current->getRequestVersion() == TUPVERSION)
                    {
                        UniAttribute<tars::BufferWriter, tars::BufferReader>  tarsAttr;
                        tarsAttr.setVersion(_current->getRequestVersion());
                        tarsAttr.decode(_current->getRequestBuffer());
                        tarsAttr.get("stat", stat);
                    }
                    else
                    {
                        _is.read(stat, 1, true);
                    }
                    tars::Int32 _ret = reportStat(stat, _current);
                    if(_current->isResponse())
                    {
                        if (_current->getRequestVersion() == TUPVERSION )
                        {
                            UniAttribute<tars::BufferWriter, tars::BufferReader>  tarsAttr;
                            tarsAttr.setVersion(_current->getRequestVersion());
                            tarsAttr.put("", _ret);
                            tarsAttr.encode(_sResponseBuffer);
                        }
                        else
                        {
                            tars::TarsOutputStream<tars::BufferWriter> _os;
                            _os.write(_ret, 0);
                            _os.swap(_sResponseBuffer);
                        }
                    }
                    return tars::TARSSERVERSUCCESS;

                }
            }
            return tars::TARSSERVERNOFUNCERR;
        }
    };


}



#endif
