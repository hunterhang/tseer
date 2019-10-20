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

#ifndef __API_LB_ALL_H_
#define __API_LB_ALL_H_

#include <string>
#include <vector>
#include <set>
#include <map>
#include "ApiLb.h"
#include "TseerAgentComm.h"


class LBAll : public LoadBalance
{
public:
    LBAll();

    ~LBAll();

    virtual int addRouter(const Tseer::RouterNodeInfo& nodeInfo);

    virtual int getRouters(vector<Tseer::RouterNodeInfo> &nodeInfoList, string &errMsg);

    virtual void clear();

    virtual int rebuild();

    virtual int statResult(const Tseer::RouterNodeInfo& req, int ret, int timeCost);

    virtual int del(const vector<Tseer::RouterNodeInfo> &nodeInfoVec);
    
private:
    std::vector<Tseer::RouterNodeInfo>     _normalNodeInfo;
    
    std::map<unsigned long long, Tseer::RouterNodeInfo> _normal;
};

#endif
