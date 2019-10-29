#ifndef COMDEF_H
#define COMDEF_H
    // 鼠标状态常量               无                       创建时改变大小     运行时改变大小         运行时创建连线             运行时改变位置
enum class MOUSE_EVENT_TYPE {NONE,/*RUNTIME_SELECT,*/CREATING_CNANGE_SIZE,RUNTIME_CHANGE_SIZE,RUNTIME_CREATE_MAGPOINT,RUNTIME_CHANGE_POS,} ;
//enum class CREATING_CNANGE_SIZE_TYPE{DEFAULTPOINT = 0x7,POINT1 = 0x0,POINT2 = 0x1,POINT3 = 0x2,POINT4 = 0x3,};
//enum class RUNTIME_CHANGE_SIZE_TYPE{DEFAULTPOINT = 0x7,POINT1 = 0x0,POINT2 = 0x1,POINT3 = 0x2,POINT4 = 0x3,};
    // 方向常量         无       西北          北   东北          东   东南      南   西南      西     起点方向随意点  终点方向随意点
enum class ORIENTION{NONE = 0,NORTHWEST = 1,NORTH,NORTHEAST,EAST,SOUTHEAST,SOUTH,SOUTHWEST,WEST,STARTPOINT = 9,ENDPOINT = 10,};
    // 箭头类型             0默认无    1箭头   2实心三角箭头 3空心三角箭头
enum class LINE_HEAD_TYPE{ARROW0 = 0,ARROW1,ARROW2,ARROW3};
    // 图形类型             无   矩形  菱形      圆角矩形    圆形  线性  梯形
enum class PaintChartType{NONE,RECT,DIAMOND,ROUNDRECT,ELLIPSE,LINE,TRAPEZOID};

#endif // COMDEF_H
