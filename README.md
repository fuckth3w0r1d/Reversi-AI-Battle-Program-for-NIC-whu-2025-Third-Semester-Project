## 这是一个黑白棋ai对战模拟程序
这个程序来源于小学期课程项目，感谢我的组员和我一起开发了这个简单的黑白棋ai程序<br>
## 如何开始
在`code/`目录下存在`player.h`和`computer.h`两个文件。你可以编辑这两个文件的内容来实现双方程序模拟黑白棋对战。不要更改这两个头文件的名字。注意必须为如下格式<br>
```
/**
 * @file player.h
 * @author yangboyang@jisuanke.com
 * @copyright jisuanke.com
 * @date 2021-07-01
 */

#include <string.h>
#include "../include/playerbase.h"
#include <stdio.h>
#include <iostream>

void init(struct Player *player) {
	// This function will be executed at the begin of each game, only once.
}

struct Point place(struct Player *player) {
	return initPoint(-1, -1);   // give up
}
```
以上是主要的两个接口函数。其他结构体和函数定义也能在`include/playerbase.h`中找到<br>`init`函数可以自行使用（也可以不用）。`place`函数是你的落子函数，返回你的落子位置选择。除此之外你可以定义任何函数来供自己使用，只要最后通过`place`函数返回返回`initPoint(x,y)`来表示你的落子选择即可。返回`initPoint(-1,-1)`表示跳过你的回合<br>非法落子(包括跳过不必跳过的回合)和思考超时（100ms限制）都会直接判负。<br>关于黑白棋的规则就不赘述了，感兴趣可以自己了解<br>
完成对战双方的函数后，你可以运行`run.sh`来模拟对战。你可以加入 `--visible`选项来可视化对战过程<br>
地图数据可以自己编辑，在`data/`目录下，注意只能实现8*8 10*10 12*12三种尺寸的棋盘。注意格式：o代表敌方棋子，O代表我方棋子。地图空格可以填入正整数来代表分值。要更改对战地图请编辑`run.sh`文件<br>
`src/my_player.h`，以及当前的`code/player.h`和`code/computer.h`都是笔者和小组成员一起开发的同一个ai程序,获得了我们年级的亚军(doge)<br>你可以更改`code/player.h`或者`code/computer.h`来模拟两方程序对战<br>
祝玩得开心！
