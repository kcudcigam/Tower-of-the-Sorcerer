### Tower of the Sorcerer

基于 [SFML 2.6.2](https://www.sfml-dev.org/), [nlohmann-json](https://github.com/nlohmann/json) 实现的简易魔塔小游戏

### Compiler

利用 cmake 进行编译，仅支持 64 位 windows 环境

编译器版本: gcc version 13.1.0 (MinGW-W64 x86_64-msvcrt-posix-seh)

### 一些改动/Feature

- 图鉴界面按左右方向键切换

- 战斗界面按 Enter 键可跳过攻击环节

- 门/道具，均需靠近后按 F 键使用，道具拾取后即被使用

- 板甲名称更改为护符，属性不变

- 玩家初始最大血量设为 50，仅可通过使用生命之石提高

- 地图上新增宝箱，会随机掉落小/大血瓶与钥匙

- 战胜怪物有 30% 概率获得战利品，种类在图鉴中显示

- 玩家如果位于岩浆地面每秒扣除 5 滴血量，并会给玩家带来僵直 debuff

- 新增精英/噩梦史莱姆酱，蝙蝠分为吸血蝙蝠与普通蝙蝠，仅有吸血蝙蝠有吸血特性
  
- 除第一关外地图均远大于 10 * 10

- 怪物手册仅会显示本层中出现的怪物
