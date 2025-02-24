
# XConfig

一个对GTA三部曲移动版进行了改进与修复的插件。
A plugin that brings improvements and fixes to GTA Trilogy Mobile.

## 支持版本

其中，NF代表网飞版，R*代表R星版（这两个版本在游戏内容上毫无区别）；对勾“√”代表支持，对勾加星号“\*”代表部分支持，问号“?”表示理论可行但无对应mod安装包，叉号“×”代表不支持，横杠“—”代表不存在这个版本。

| **游戏** | **III** |  | **VC** |  | **SA** |  |
|---|---|---|---|---|---|---|
| **版本** | NF | R* | NF | R* | NF | R* |
| **1.72** | √ | √ | √ | √ | √ | √ |
| **1.83** | ? | √ | ? | √ | — | — |
| **1.86** | — | — | — | — | ? | √ |
| **1.90** | × | — | × | — | — | — |

## 功能

### 自动保存

**[SA][VC][III]** 可以每隔一个特定的时间进行自动保存，而不像原来那样只在任务开始与完成时进行保存。保存到插槽sf10<sup>**[SA]**</sup>/sf9<sup>**[VC][III]**</sup>。（当玩家在车库内保存时会死亡，因此本插件不在车库内保存，但可能出现罕见情况保存而秒杀了，重载刚才存档即可<sup>**仅[SA][VC]有此bug**</sup>）

- `Enabled`： 功能开启。
- `IntervalTime`： 间隔时间，以秒为单位，默认20秒，最低10秒。
- `SaveInInteriors`： 是否在室内空间保存。默认开启<sup>**[VC]**</sup>/不建议开启，以防遇见与enex相关的bug<sup>**[SA]**</sup>。

### 显示FPS

**[SA][VC][III]** 在屏幕左上角显示每秒帧数，根据数值，颜色会渐变变化，从红色到绿色。问题<sup>**仅[SA]**</sup>：当开启武器轮盘或电台轮盘时，显示的FPS值会增大约5到10倍。

- `ShowFPS`： 功能开启。
- `MaxFPSToShowColor`： 显示为绿色的最小FPS值。
- `UseModernFonts`： **[SA]** `1`使用菜单样式的扁字体（Bank Gothic），`0`使用字幕样式的等线字体。**[VC]** `1`使用细长的等线字体，`0`使用飘逸字体（Rage Italic Com）。**[III]** `1`使用字幕样式的等线，`0`使用标题样式的粗字体（Pricedown）。

### 新增的作弊码

`RestoreDebuggingCheats`：**[SA][VC]** 恢复十周年版被隐藏起来的作弊码。不区分大小写。无需在末尾输入中文说明。

**仅[SA]** `IncreaseTimesCheated`：激活这些作弊码是否增加统计信息中的作弊次数。

**[VC]** 将不会增加统计信息中的作弊次数。

以下为可用作弊码列表：

- TimeTraveler：**[SA]** 时间前进4小时。
- SecretSpySet：**[SA]** 武器包4，包含火神机枪、Vibrator、夜视镜和热成像夜视镜。后两者交替出现。
- FreezeIt：**[SA]** 锁定时间。游戏的阴影可能会出现问题。
- TrueGod：**[SA]** 无敌，玩家不会受到任何伤害，包括没开降落伞着地，车辆也是无敌，但强制使其爆炸仍会杀死玩家；开启后警察不可能逮捕玩家。**[VC]** 免疫除溺水的伤害外的所有伤害。车辆也是无敌，但爆炸仍会杀死玩家。
- NoPity：**[SA]** 跳过（直接完成）当前任务，极少数任务不可跳过，和十周年手机版一样。
- Teleport：**[SA|特色]** 传送到地图导航点位置。**注意：** 若标点较远，则需很长时间加载，甚至让玩家卡进地图中，此时需要在附近标点，再次传送。
- SlamDoors：**[SA]** 打开玩家载具全部车门，包括引擎盖、后备厢门，再输则关闭。
- **[SA|特色]** 输入模型ID，紧跟字母S（不区分大小写）可刷出对应车辆，除火车外。
- **[SA|特色]** 输入模型ID，紧跟字母T（不区分大小写）可将主角皮肤改为对应NPC皮肤（CJ是0，即输入`0t`）。bug：由于最终版的引擎原因，变换后武器模型会悬浮，喷气背包位置偏移，且玩家不能下蹲。参见[MixMods的电脑版对应脚本页面](https://www.mixmods.com.br/2022/01/simple-skin-selector-ped-creator/)。

### 其他

- **[SA][VC][III]** `FixMissingTextKey`：修复装了某些.pak模组包（如一些画质包）后，游戏的一些文字变为一长串“XXX missing”（文本缺失）。bug：重载存档时第一个显示的文本（右下角的地名或者任务名）会变为别的文字，但不影响正常游戏。
- **[SA|特色]** `FixRadarIconInSeaGlitch`： 自动检测并修复CV（王氏车行）任务点和2个安全屋的图标在水中（地图中心）的最终版特有bug，无需开新档。
- **[SA|仅1.72]** `AllowAutoAimingOnRFMG`：启用杠杆步枪和火神机枪的自动瞄准功能。（1.86版无效）
- **[SA|仅1.72]** `AbleToSkipCredits`：在大结局后鸣谢名单中显示跳过按钮。
- **[SA]** `NotForcedToCloseVehDoor`：下车时拉住左下角摇杆可以不关门。
- **[SA]** `ClimbOnAnyVehicle`：让车辆可以像建筑物一样能够被攀爬上。
- **[SA|部分可用]** `FixVehMovingObjs`：水泥罐车新加按钮，可以控制水泥罐旋转速度；消防云梯车（FIRELA）增加调节云梯高度的功能（镜头高度会出现严重bug）。
- **[SA]** `ColouredZoneNames`： 屏幕右下角显示地名时，还会显示帮派地盘的颜色。这是在原版游戏损坏的功能，原版只会在一个地盘由多个帮派控制时才显示（官方把与/或条件弄混）。颜色计算方式忽视帮派密度而不是原版的SilentPatch（二次方变换）。
- **[SA]** `FixMissingShootBtnForPredator`：修复不显示驾驶捕食者（Predator）这艘船时的固定机炮开火按钮（最终版III和VC的这艘船都有开火按钮，SA因为bug没有）
- **[SA]** `PlaneExplodeDisappearFix`：修复玩家驾驶的飞机在爆炸后消失，而不留残骸的bug。
- **[SA]** `SprintOnAnySurface`：在绝大多数室内空间可以冲刺。即原版和十周年的插件“Sprint Everywhere”。
- **[SA|未测试]** `FixWrongCarCol`：修正carcols.dat中颜色#98（大烟哥蓝色汽车所用颜色）。
- **[VC|部分可用]** `AbleToSkipTelephoneCall`：接听电话时可以按电话按钮挂断电话。功能bug：一旦挂电话之后，后续来电接听将会自动挂断
- **[VC|未测试]** `AllowAutoAimingOnMG`：启用火神机枪的自动瞄准功能。功能bug：不可用
- **[VC|未测试]** `FixLeafLinksBridgesTraffic`：修复高尔夫球场旁边那个大桥没有车流的bug。功能bug：不可用
- **[III]** `MafiaDontUseShotgun`：家族黑手党在游戏中后期使用AK47而不是霰弹枪，以降低难度。不影响任务“浓缩咖啡外卖！Espresso-2-Go!”与“血脉喷张Big'N'Veiny”。
- **[III]** `FixFBICarColor`：修复FBI汽车追击型颜色为纯黑的遗留问题。
