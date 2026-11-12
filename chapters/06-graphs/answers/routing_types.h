#ifndef CH06_ROUTING_TYPES_H
#define CH06_ROUTING_TYPES_H

#include <stdint.h>

// 功能：定义综合应用题路由信息块中的链路、网络前缀、路由弧和路由器链结点结构。
// 来源：《2027数据结构》第6章 6.3.4 综合应用题10答案；PDF第271页；书页第259页。
typedef struct {
    uint32_t ID;
    uint32_t IP;
} LinkNode;

typedef struct {
    uint32_t Prefix;
    uint32_t Mask;
} NetNode;

typedef union {
    LinkNode LNode;
    NetNode NNode;
} RoutePayload;

typedef struct RouteArc {
    int Flag;
    RoutePayload LinkORNet;
    uint32_t Metric;
    struct RouteArc *next;
} RouteArc;

typedef struct RouterNode {
    uint32_t RouterID;
    RouteArc *IN_link;
    struct RouterNode *next;
} RouterNode;

// 功能：释放由堆分配的路由器链及各路由器拥有的入链路弧链。
// 来源：C17 动态内存所有权辅助接口；RouterNode 与 RouteArc 由调用者按链表规则独占。
void RoutingRouterListDestroy(RouterNode *routers);

#endif
