## 这是一个黑白棋ai对战模拟程序
这个程序来源于小学期课程项目<br>
## 如何开始
在code/目录下存在player.h和computer.h两个文件。你可以编辑这两个文件的内容来实现双方模拟黑白棋对战。不要更改这两个头文件的名字。注意必须为如下格式<br>
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
以上是主要的两个接口函数。init函数可以自行使用。place函数是你的落子函数，返回你的落子位置选择。除此之外你可以定义任何函数来供自己使用，只要最后通过place函数返回你的落子选择即可。<br>
完成对战双方的函数后，你可以运行./run.sh来模拟对战。你可以加入 --visible选项来可视化对战过程<br>
地图数据可以自己编辑，在data/目录下，注意只能实现8*8 10*10 12*12三种尺寸的棋盘。注意格式：o代表敌方棋子，O代表我方棋子。地图空格可以填入正整数来代表分值。要更改对战地图请编辑./run.sh文件<br>
在src/目录下有笔者和小组成员一起开发的ai程序，你可以试着复制其内容到code/player.h或者code/computer.h中来和其他程序对战<br>
祝玩得开心！
