// **********************************************************************
// This file was generated by a TARS parser!
// TARS version 1.1.0.
// **********************************************************************

#ifndef __TSEERAGENTUPDATE_H_
#define __TSEERAGENTUPDATE_H_

#include <map>
#include <string>
#include <vector>
#include "tup/Tars.h"
using namespace std;
#include "servant/ServantProxy.h"
#include "servant/Servant.h"
#include "promise/promise.h"


namespace Tseer
{
    struct AgentConfig : public tars::TarsStructBase
    {
    public:
        static string className()
        {
            return "Tseer.AgentConfig";
        }
        static string MD5()
        {
            return "325d87d477a8cf7a6468ed6bb39da964";
        }
        AgentConfig()
        :locator(""),nodeIp("")
        {
        }
        void resetDefautlt()
        {
            locator = "";
            nodeIp = "";
        }
        template<typename WriterT>
        void writeTo(tars::TarsOutputStream<WriterT>& _os) const
        {
            _os.write(locator, 0);
            _os.write(nodeIp, 1);
        }
        template<typename ReaderT>
        void readFrom(tars::TarsInputStream<ReaderT>& _is)
        {
            resetDefautlt();
            _is.read(locator, 0, true);
            _is.read(nodeIp, 1, true);
        }
        ostream& display(ostream& _os, int _level=0) const
        {
            tars::TarsDisplayer _ds(_os, _level);
            _ds.display(locator,"locator");
            _ds.display(nodeIp,"nodeIp");
            return _os;
        }
        ostream& displaySimple(ostream& _os, int _level=0) const
        {
            tars::TarsDisplayer _ds(_os, _level);
            _ds.displaySimple(locator, true);
            _ds.displaySimple(nodeIp, false);
            return _os;
        }
    public:
        std::string locator;
        std::string nodeIp;
    };
    inline bool operator==(const AgentConfig&l, const AgentConfig&r)
    {
        return l.locator == r.locator && l.nodeIp == r.nodeIp;
    }
    inline bool operator!=(const AgentConfig&l, const AgentConfig&r)
    {
        return !(l == r);
    }


    /* callback of async proxy for client */
    class UpdatePrxCallback: public tars::ServantProxyCallback
    {
    public:
        virtual ~UpdatePrxCallback(){}
        virtual void callback_uninstall(tars::Int32 ret,  const std::string& result)
        { throw std::runtime_error("callback_uninstall() override incorrect."); }
        virtual void callback_uninstall_exception(tars::Int32 ret)
        { throw std::runtime_error("callback_uninstall_exception() override incorrect."); }

        virtual void callback_updateConfig(tars::Int32 ret,  const std::string& result)
        { throw std::runtime_error("callback_updateConfig() override incorrect."); }
        virtual void callback_updateConfig_exception(tars::Int32 ret)
        { throw std::runtime_error("callback_updateConfig_exception() override incorrect."); }

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
            static ::std::string __Update_all[]=
            {
                "uninstall",
                "updateConfig"
            };
            pair<string*, string*> r = equal_range(__Update_all, __Update_all+2, string(msg->request.sFuncName));
            if(r.first == r.second) return tars::TARSSERVERNOFUNCERR;
            switch(r.first - __Update_all)
            {
                case 0:
                {
                    if (msg->response.iRet != tars::TARSSERVERSUCCESS)
                    {
                        callback_uninstall_exception(msg->response.iRet);

                        return msg->response.iRet;
                    }
                    tars::TarsInputStream<tars::BufferReader> _is;

                    _is.setBuffer(msg->response.sBuffer);
                    tars::Int32 _ret;
                    _is.read(_ret, 0, true);

                    std::string result;
                    _is.read(result, 1, true);
                    CallbackThreadData * pCbtd = CallbackThreadData::getData();
                    assert(pCbtd != NULL);

                    pCbtd->setResponseContext(msg->response.context);

                    callback_uninstall(_ret, result);

                    pCbtd->delResponseContext();

                    return tars::TARSSERVERSUCCESS;

                }
                case 1:
                {
                    if (msg->response.iRet != tars::TARSSERVERSUCCESS)
                    {
                        callback_updateConfig_exception(msg->response.iRet);

                        return msg->response.iRet;
                    }
                    tars::TarsInputStream<tars::BufferReader> _is;

                    _is.setBuffer(msg->response.sBuffer);
                    tars::Int32 _ret;
                    _is.read(_ret, 0, true);

                    std::string result;
                    _is.read(result, 2, true);
                    CallbackThreadData * pCbtd = CallbackThreadData::getData();
                    assert(pCbtd != NULL);

                    pCbtd->setResponseContext(msg->response.context);

                    callback_updateConfig(_ret, result);

                    pCbtd->delResponseContext();

                    return tars::TARSSERVERSUCCESS;

                }
            }
            return tars::TARSSERVERNOFUNCERR;
        }

    };
    typedef tars::TC_AutoPtr<UpdatePrxCallback> UpdatePrxCallbackPtr;

    /* callback of promise async proxy for client */
    class UpdatePrxCallbackPromise: public tars::ServantProxyCallback
    {
    public:
        virtual ~UpdatePrxCallbackPromise(){}
    public:
        struct Promiseuninstall: virtual public TC_HandleBase
        {
        public:
            tars::Int32 _ret;
            std::string result;
            map<std::string, std::string> _mRspContext;
        };
        
        typedef tars::TC_AutoPtr< UpdatePrxCallbackPromise::Promiseuninstall > PromiseuninstallPtr;

        UpdatePrxCallbackPromise(const promise::Promise< UpdatePrxCallbackPromise::PromiseuninstallPtr > &promise)
        : _promise_uninstall(promise)
        {}
        
        virtual void callback_uninstall(const UpdatePrxCallbackPromise::PromiseuninstallPtr &ptr)
        {
            _promise_uninstall.setValue(ptr);
        }
        virtual void callback_uninstall_exception(tars::Int32 ret)
        {
            std::string str("");
            str += "Function:uninstall_exception|Ret:";
            str += TC_Common::tostr(ret);
            _promise_uninstall.setException(promise::copyException(str, ret));
        }

    protected:
        promise::Promise< UpdatePrxCallbackPromise::PromiseuninstallPtr > _promise_uninstall;

    public:
        struct PromiseupdateConfig: virtual public TC_HandleBase
        {
        public:
            tars::Int32 _ret;
            std::string result;
            map<std::string, std::string> _mRspContext;
        };
        
        typedef tars::TC_AutoPtr< UpdatePrxCallbackPromise::PromiseupdateConfig > PromiseupdateConfigPtr;

        UpdatePrxCallbackPromise(const promise::Promise< UpdatePrxCallbackPromise::PromiseupdateConfigPtr > &promise)
        : _promise_updateConfig(promise)
        {}
        
        virtual void callback_updateConfig(const UpdatePrxCallbackPromise::PromiseupdateConfigPtr &ptr)
        {
            _promise_updateConfig.setValue(ptr);
        }
        virtual void callback_updateConfig_exception(tars::Int32 ret)
        {
            std::string str("");
            str += "Function:updateConfig_exception|Ret:";
            str += TC_Common::tostr(ret);
            _promise_updateConfig.setException(promise::copyException(str, ret));
        }

    protected:
        promise::Promise< UpdatePrxCallbackPromise::PromiseupdateConfigPtr > _promise_updateConfig;

    public:
        virtual int onDispatch(tars::ReqMessagePtr msg)
        {
            static ::std::string __Update_all[]=
            {
                "uninstall",
                "updateConfig"
            };

            pair<string*, string*> r = equal_range(__Update_all, __Update_all+2, string(msg->request.sFuncName));
            if(r.first == r.second) return tars::TARSSERVERNOFUNCERR;
            switch(r.first - __Update_all)
            {
                case 0:
                {
                    if (msg->response.iRet != tars::TARSSERVERSUCCESS)
                    {
                        callback_uninstall_exception(msg->response.iRet);

                        return msg->response.iRet;
                    }
                    tars::TarsInputStream<tars::BufferReader> _is;

                    _is.setBuffer(msg->response.sBuffer);

                    UpdatePrxCallbackPromise::PromiseuninstallPtr ptr = new UpdatePrxCallbackPromise::Promiseuninstall();

                    try
                    {
                        _is.read(ptr->_ret, 0, true);

                        _is.read(ptr->result, 1, true);
                    }
                    catch(std::exception &ex)
                    {
                        callback_uninstall_exception(tars::TARSCLIENTDECODEERR);

                        return tars::TARSCLIENTDECODEERR;
                    }
                    catch(...)
                    {
                        callback_uninstall_exception(tars::TARSCLIENTDECODEERR);

                        return tars::TARSCLIENTDECODEERR;
                    }

                    ptr->_mRspContext = msg->response.context;

                    callback_uninstall(ptr);

                    return tars::TARSSERVERSUCCESS;

                }
                case 1:
                {
                    if (msg->response.iRet != tars::TARSSERVERSUCCESS)
                    {
                        callback_updateConfig_exception(msg->response.iRet);

                        return msg->response.iRet;
                    }
                    tars::TarsInputStream<tars::BufferReader> _is;

                    _is.setBuffer(msg->response.sBuffer);

                    UpdatePrxCallbackPromise::PromiseupdateConfigPtr ptr = new UpdatePrxCallbackPromise::PromiseupdateConfig();

                    try
                    {
                        _is.read(ptr->_ret, 0, true);

                        _is.read(ptr->result, 2, true);
                    }
                    catch(std::exception &ex)
                    {
                        callback_updateConfig_exception(tars::TARSCLIENTDECODEERR);

                        return tars::TARSCLIENTDECODEERR;
                    }
                    catch(...)
                    {
                        callback_updateConfig_exception(tars::TARSCLIENTDECODEERR);

                        return tars::TARSCLIENTDECODEERR;
                    }

                    ptr->_mRspContext = msg->response.context;

                    callback_updateConfig(ptr);

                    return tars::TARSSERVERSUCCESS;

                }
            }
            return tars::TARSSERVERNOFUNCERR;
        }

    };
    typedef tars::TC_AutoPtr<UpdatePrxCallbackPromise> UpdatePrxCallbackPromisePtr;

    /* callback of coroutine async proxy for client */
    class UpdateCoroPrxCallback: public UpdatePrxCallback
    {
    public:
        virtual ~UpdateCoroPrxCallback(){}
    public:
        virtual const map<std::string, std::string> & getResponseContext() const { return _mRspContext; }

        virtual void setResponseContext(const map<std::string, std::string> &mContext) { _mRspContext = mContext; }

    public:
        int onDispatch(tars::ReqMessagePtr msg)
        {
            static ::std::string __Update_all[]=
            {
                "uninstall",
                "updateConfig"
            };

            pair<string*, string*> r = equal_range(__Update_all, __Update_all+2, string(msg->request.sFuncName));
            if(r.first == r.second) return tars::TARSSERVERNOFUNCERR;
            switch(r.first - __Update_all)
            {
                case 0:
                {
                    if (msg->response.iRet != tars::TARSSERVERSUCCESS)
                    {
                        callback_uninstall_exception(msg->response.iRet);

                        return msg->response.iRet;
                    }
                    tars::TarsInputStream<tars::BufferReader> _is;

                    _is.setBuffer(msg->response.sBuffer);
                    try
                    {
                        tars::Int32 _ret;
                        _is.read(_ret, 0, true);

                        std::string result;
                        _is.read(result, 1, true);
                        setResponseContext(msg->response.context);

                        callback_uninstall(_ret, result);

                    }
                    catch(std::exception &ex)
                    {
                        callback_uninstall_exception(tars::TARSCLIENTDECODEERR);

                        return tars::TARSCLIENTDECODEERR;
                    }
                    catch(...)
                    {
                        callback_uninstall_exception(tars::TARSCLIENTDECODEERR);

                        return tars::TARSCLIENTDECODEERR;
                    }

                    return tars::TARSSERVERSUCCESS;

                }
                case 1:
                {
                    if (msg->response.iRet != tars::TARSSERVERSUCCESS)
                    {
                        callback_updateConfig_exception(msg->response.iRet);

                        return msg->response.iRet;
                    }
                    tars::TarsInputStream<tars::BufferReader> _is;

                    _is.setBuffer(msg->response.sBuffer);
                    try
                    {
                        tars::Int32 _ret;
                        _is.read(_ret, 0, true);

                        std::string result;
                        _is.read(result, 2, true);
                        setResponseContext(msg->response.context);

                        callback_updateConfig(_ret, result);

                    }
                    catch(std::exception &ex)
                    {
                        callback_updateConfig_exception(tars::TARSCLIENTDECODEERR);

                        return tars::TARSCLIENTDECODEERR;
                    }
                    catch(...)
                    {
                        callback_updateConfig_exception(tars::TARSCLIENTDECODEERR);

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
    typedef tars::TC_AutoPtr<UpdateCoroPrxCallback> UpdateCoroPrxCallbackPtr;

    /* proxy for client */
    class UpdateProxy : public tars::ServantProxy
    {
    public:
        typedef map<string, string> TARS_CONTEXT;
        tars::Int32 uninstall(std::string &result,const map<string, string> &context = TARS_CONTEXT(),map<string, string> * pResponseContext = NULL)
        {
            tars::TarsOutputStream<tars::BufferWriter> _os;
            _os.write(result, 1);
            tars::ResponsePacket rep;
            std::map<string, string> _mStatus;
            tars_invoke(tars::TARSNORMAL,"uninstall", _os.getByteBuffer(), context, _mStatus, rep);
            if(pResponseContext)
            {
                *pResponseContext = rep.context;
            }

            tars::TarsInputStream<tars::BufferReader> _is;
            _is.setBuffer(rep.sBuffer);
            tars::Int32 _ret;
            _is.read(_ret, 0, true);
            _is.read(result, 1, true);
            return _ret;
        }

        void async_uninstall(UpdatePrxCallbackPtr callback,const map<string, string>& context = TARS_CONTEXT())
        {
            tars::TarsOutputStream<tars::BufferWriter> _os;
            std::map<string, string> _mStatus;
            tars_invoke_async(tars::TARSNORMAL,"uninstall", _os.getByteBuffer(), context, _mStatus, callback);
        }
        
        promise::Future< UpdatePrxCallbackPromise::PromiseuninstallPtr > promise_async_uninstall(const map<string, string>& context)
        {
            promise::Promise< UpdatePrxCallbackPromise::PromiseuninstallPtr > promise;
            UpdatePrxCallbackPromisePtr callback = new UpdatePrxCallbackPromise(promise);

            tars::TarsOutputStream<tars::BufferWriter> _os;
            std::map<string, string> _mStatus;
            tars_invoke_async(tars::TARSNORMAL,"uninstall", _os.getByteBuffer(), context, _mStatus, callback);

            return promise.getFuture();
        }

        void coro_uninstall(UpdateCoroPrxCallbackPtr callback,const map<string, string>& context = TARS_CONTEXT())
        {
            tars::TarsOutputStream<tars::BufferWriter> _os;
            std::map<string, string> _mStatus;
            tars_invoke_async(tars::TARSNORMAL,"uninstall", _os.getByteBuffer(), context, _mStatus, callback, true);
        }

        tars::Int32 updateConfig(const Tseer::AgentConfig & cfg,std::string &result,const map<string, string> &context = TARS_CONTEXT(),map<string, string> * pResponseContext = NULL)
        {
            tars::TarsOutputStream<tars::BufferWriter> _os;
            _os.write(cfg, 1);
            _os.write(result, 2);
            tars::ResponsePacket rep;
            std::map<string, string> _mStatus;
            tars_invoke(tars::TARSNORMAL,"updateConfig", _os.getByteBuffer(), context, _mStatus, rep);
            if(pResponseContext)
            {
                *pResponseContext = rep.context;
            }

            tars::TarsInputStream<tars::BufferReader> _is;
            _is.setBuffer(rep.sBuffer);
            tars::Int32 _ret;
            _is.read(_ret, 0, true);
            _is.read(result, 2, true);
            return _ret;
        }

        void async_updateConfig(UpdatePrxCallbackPtr callback,const Tseer::AgentConfig &cfg,const map<string, string>& context = TARS_CONTEXT())
        {
            tars::TarsOutputStream<tars::BufferWriter> _os;
            _os.write(cfg, 1);
            std::map<string, string> _mStatus;
            tars_invoke_async(tars::TARSNORMAL,"updateConfig", _os.getByteBuffer(), context, _mStatus, callback);
        }
        
        promise::Future< UpdatePrxCallbackPromise::PromiseupdateConfigPtr > promise_async_updateConfig(const Tseer::AgentConfig &cfg,const map<string, string>& context)
        {
            promise::Promise< UpdatePrxCallbackPromise::PromiseupdateConfigPtr > promise;
            UpdatePrxCallbackPromisePtr callback = new UpdatePrxCallbackPromise(promise);

            tars::TarsOutputStream<tars::BufferWriter> _os;
            _os.write(cfg, 1);
            std::map<string, string> _mStatus;
            tars_invoke_async(tars::TARSNORMAL,"updateConfig", _os.getByteBuffer(), context, _mStatus, callback);

            return promise.getFuture();
        }

        void coro_updateConfig(UpdateCoroPrxCallbackPtr callback,const Tseer::AgentConfig &cfg,const map<string, string>& context = TARS_CONTEXT())
        {
            tars::TarsOutputStream<tars::BufferWriter> _os;
            _os.write(cfg, 1);
            std::map<string, string> _mStatus;
            tars_invoke_async(tars::TARSNORMAL,"updateConfig", _os.getByteBuffer(), context, _mStatus, callback, true);
        }

        UpdateProxy* tars_hash(int64_t key)
        {
            return (UpdateProxy*)ServantProxy::tars_hash(key);
        }

        UpdateProxy* tars_consistent_hash(int64_t key)
        {
            return (UpdateProxy*)ServantProxy::tars_consistent_hash(key);
        }

        UpdateProxy* tars_set_timeout(int msecond)
        {
            return (UpdateProxy*)ServantProxy::tars_set_timeout(msecond);
        }

    };
    typedef tars::TC_AutoPtr<UpdateProxy> UpdatePrx;

    /* servant for server */
    class Update : public tars::Servant
    {
    public:
        virtual ~Update(){}
        virtual tars::Int32 uninstall(std::string &result,tars::TarsCurrentPtr current) = 0;
        static void async_response_uninstall(tars::TarsCurrentPtr current, tars::Int32 _ret, const std::string &result)
        {
            if (current->getRequestVersion() == TUPVERSION )
            {
                UniAttribute<tars::BufferWriter, tars::BufferReader>  tarsAttr;
                tarsAttr.setVersion(current->getRequestVersion());
                tarsAttr.put("", _ret);
                tarsAttr.put("result", result);

                vector<char> sTupResponseBuffer;
                tarsAttr.encode(sTupResponseBuffer);
                current->sendResponse(tars::TARSSERVERSUCCESS, sTupResponseBuffer);
            }
            else
            {
                tars::TarsOutputStream<tars::BufferWriter> _os;
                _os.write(_ret, 0);

                _os.write(result, 1);

                current->sendResponse(tars::TARSSERVERSUCCESS, _os.getByteBuffer());
            }
        }

        virtual tars::Int32 updateConfig(const Tseer::AgentConfig & cfg,std::string &result,tars::TarsCurrentPtr current) = 0;
        static void async_response_updateConfig(tars::TarsCurrentPtr current, tars::Int32 _ret, const std::string &result)
        {
            if (current->getRequestVersion() == TUPVERSION )
            {
                UniAttribute<tars::BufferWriter, tars::BufferReader>  tarsAttr;
                tarsAttr.setVersion(current->getRequestVersion());
                tarsAttr.put("", _ret);
                tarsAttr.put("result", result);

                vector<char> sTupResponseBuffer;
                tarsAttr.encode(sTupResponseBuffer);
                current->sendResponse(tars::TARSSERVERSUCCESS, sTupResponseBuffer);
            }
            else
            {
                tars::TarsOutputStream<tars::BufferWriter> _os;
                _os.write(_ret, 0);

                _os.write(result, 2);

                current->sendResponse(tars::TARSSERVERSUCCESS, _os.getByteBuffer());
            }
        }

    public:
        int onDispatch(tars::TarsCurrentPtr _current, vector<char> &_sResponseBuffer)
        {
            static ::std::string __Tseer__Update_all[]=
            {
                "uninstall",
                "updateConfig"
            };

            pair<string*, string*> r = equal_range(__Tseer__Update_all, __Tseer__Update_all+2, _current->getFuncName());
            if(r.first == r.second) return tars::TARSSERVERNOFUNCERR;
            switch(r.first - __Tseer__Update_all)
            {
                case 0:
                {
                    tars::TarsInputStream<tars::BufferReader> _is;
                    _is.setBuffer(_current->getRequestBuffer());
                    std::string result;
                    if (_current->getRequestVersion() == TUPVERSION)
                    {
                        UniAttribute<tars::BufferWriter, tars::BufferReader>  tarsAttr;
                        tarsAttr.setVersion(_current->getRequestVersion());
                        tarsAttr.decode(_current->getRequestBuffer());
                        tarsAttr.getByDefault("result", result, result);
                    }
                    else
                    {
                        _is.read(result, 1, false);
                    }
                    tars::Int32 _ret = uninstall(result, _current);
                    if(_current->isResponse())
                    {
                        if (_current->getRequestVersion() == TUPVERSION )
                        {
                            UniAttribute<tars::BufferWriter, tars::BufferReader>  tarsAttr;
                            tarsAttr.setVersion(_current->getRequestVersion());
                            tarsAttr.put("", _ret);
                            tarsAttr.put("result", result);
                            tarsAttr.encode(_sResponseBuffer);
                        }
                        else
                        {
                            tars::TarsOutputStream<tars::BufferWriter> _os;
                            _os.write(_ret, 0);
                            _os.write(result, 1);
                            _os.swap(_sResponseBuffer);
                        }
                    }
                    return tars::TARSSERVERSUCCESS;

                }
                case 1:
                {
                    tars::TarsInputStream<tars::BufferReader> _is;
                    _is.setBuffer(_current->getRequestBuffer());
                    Tseer::AgentConfig cfg;
                    std::string result;
                    if (_current->getRequestVersion() == TUPVERSION)
                    {
                        UniAttribute<tars::BufferWriter, tars::BufferReader>  tarsAttr;
                        tarsAttr.setVersion(_current->getRequestVersion());
                        tarsAttr.decode(_current->getRequestBuffer());
                        tarsAttr.get("cfg", cfg);
                        tarsAttr.getByDefault("result", result, result);
                    }
                    else
                    {
                        _is.read(cfg, 1, true);
                        _is.read(result, 2, false);
                    }
                    tars::Int32 _ret = updateConfig(cfg,result, _current);
                    if(_current->isResponse())
                    {
                        if (_current->getRequestVersion() == TUPVERSION )
                        {
                            UniAttribute<tars::BufferWriter, tars::BufferReader>  tarsAttr;
                            tarsAttr.setVersion(_current->getRequestVersion());
                            tarsAttr.put("", _ret);
                            tarsAttr.put("result", result);
                            tarsAttr.encode(_sResponseBuffer);
                        }
                        else
                        {
                            tars::TarsOutputStream<tars::BufferWriter> _os;
                            _os.write(_ret, 0);
                            _os.write(result, 2);
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
