#include "routing_types.h"

#include <stdlib.h>

// 功能：释放由堆分配的路由器链及各路由器拥有的入链路弧链。
// 来源：C17 动态内存所有权辅助接口；RouterNode 与 RouteArc 由调用者按链表规则独占。
void RoutingRouterListDestroy(RouterNode *routers) {
    while (routers != NULL) {
        RouterNode *next_router = routers->next;
        RouteArc *arc = routers->IN_link;
        while (arc != NULL) {
            RouteArc *next_arc = arc->next;
            free(arc);
            arc = next_arc;
        }
        free(routers);
        routers = next_router;
    }
}
