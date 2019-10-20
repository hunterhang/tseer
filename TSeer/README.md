﻿1）针对Agent做了二次修改，支持Http协议获取Ip,Port . 支持Http协议上报调用状态。

2）支持mysql 存储

3）修改了DB中的Bug，见Wiki. 

4) 在TSeerAgent/test 目录 中，添加了php测试Agent接口的性能测试代码。

具体安装方法，见wiki : https://github.com/hunterhang/tseer/wiki



以下是原文描述

[Click me switch to English version](README.en.md)

## TSeer

TSeer是一套服务注册发现容错的解决方案，是对Tars名字服务功能的轻量化。在腾讯浏览器、应用宝、管家、手机书城、腾讯文学、广点通等众多业务中广泛采用，目前日均承载百亿级别的请求量。

在服务发现的核心功能之上，TSeer还支持多种优秀的负载均衡算法，提供可靠的故障容错策略。针对发展迅速的海量服务，还支持就近接入，按SET逻辑分组，全量调度三种不同的路由策略。实现了高度智能的调度优化，有效解决了业务跨地区跨机房调用等难题,极大提升服务的可用性和调用质量。

TSeer拥有web管理界面和API接入两种方式可供用户根据需求自由选择，通过代理节点和代理服务器机制为需要频繁发布变更的业务提供透明的服务发现功能，学习成本很低，操作也很方便，对于业务维护人员十分友好。

同时TSeer轻巧灵便，对业务的侵入性低，非Tars服务亦可无缝接入,是微服务框架中优秀的名字服务解决方案。

产品详细说明文档参见[TSeer产品介绍](Introduction.md)

## 支持平台

> * Linux

## 支持语言

> * JAVA
> * C++
> * 更多版本持续开发中...

## 安装指引

TSeer提供了一键部署脚本，安装方便快捷。详见[TSeer安装文档](Tseer_Install.md)

## api

[c++ api](docs/cplus-api-quickstart.md)

[java api](docs/seer-api-java-quickstart.md)
