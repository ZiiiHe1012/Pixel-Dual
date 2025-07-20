//
// Created by gerw on 8/20/24.
//

#include <memory>
#include "Link.h"

Link::Link(QGraphicsItem *parent) 
    : Character(parent, ":/Items/Characters/figure.png") { // 人物图片
    // 设置大小
    setScale(1.5); 
    // 下蹲图片
    setCrouchImage(":Items/Characters/down.png");
}
