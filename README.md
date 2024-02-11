# XConfig
一个对GTA三部曲移动版进行了改进与修复的插件。
A plugin that brings improvements and fixes to GTA Trilogy Mobile.

## 功能 Features

### 圣安地列斯 For SA

#### 自动保存 Auto Save
可以每隔一个特定的时间进行自动保存，而不像原来那样只在任务开始与完成时进行保存。保存到插槽sf10。
It can save your game every certain seconds instead of save only when you starts or passes a mission. It's will save to the slot called sf10.

- `Enabled`： 功能开启。
- `IntervalTime`： 间隔时间，以秒为单位，默认20秒，最低10秒。As name, in seconds. Default value is 20s, minimum value is 10s.
- `SaveInInteriors`： 是否在室内空间保存。不建议开启，以防遇见与enex相关的bug。Saving in interiors or not. You may meet some problems about enex if you leave it open.

#### 显示FPS Show FPS
在屏幕左上角显示每秒帧数，根据数值，颜色会渐变变化，从红色到绿色。问题：当开启武器轮盘或电台轮盘时，显示的FPS值会增大约5到10倍。Frames per second is displayed in the upper left corner of the screen, and depending on the value, the color changes gradually, from red to green. Problem: When the weapon wheel or radio wheel is showing, the FPS value displayed increases by about 5 to 10 times.

- `ShowFPS`： 功能开启。
- `MaxFPSToShowColor`： 显示为绿色的最小FPS值。The minimum FPS value to display in green.
- `UseModernFonts`： 是否显示菜单样式的扁字体，而不是字幕样式的字体。Whether to display menu-style flat font instead of subtitle-style font.

#### 新增的作弊码 New Cheats
`RestoreDebuggingCheats`： 恢复十周年版被隐藏起来的作弊码。目前激活这些作弊码不会增加统计信息中的作弊次数。不区分大小写。无# XConfig
一个对GTA三部曲移动版进行了改进与修复的插件。
A plugin that brings improvements and fixes to GTA Trilogy Mobile.

## 功能 Features

### 圣安地列斯 For SA

#### 自动保存 Auto Save
可以每隔一个特定的时间进行自动保存，而不像原来那样只在任务开始与完成时进行保存。保存到插槽sf10。
It can save your game every certain seconds instead of save only when you starts or passes a mission. It's will save to the slot called sf10.

- `Enabled`： 功能开启。
- `IntervalTime`： 间隔时间，以秒为单位，默认20秒，最低10秒。As name, in seconds. Default value is 20s, minimum value is 10s.
- `SaveInInteriors`： 是否在室内空间保存。不建议开启，以防遇见与enex相关的bug。Saving in interiors or not. You may meet some problems about enex if you leave it open.

#### 显示FPS Show FPS
在屏幕左上角显示每秒帧数，根据数值，颜色会渐变变化，从红色到绿色。问题：当开启武器轮盘或电台轮盘时，显示的FPS值会增大约5到10倍。Frames per second is displayed in the upper left corner of the screen, and depending on the value, the color changes gradually, from red to green. Problem: When the weapon wheel or radio wheel is showing, the FPS value displayed increases by about 5 to 10 times.

- `ShowFPS`： 功能开启。
- `MaxFPSToShowColor`： 显示为绿色的最小FPS值。The minimum FPS value to display in green.
- `UseModernFonts`： 是否显示菜单样式的扁字体，而不是字幕样式的字体。Whether to display menu-style flat font instead of subtitle-style font.

#### 新增的作弊码 New Cheats
`RestoreDebuggingCheats`： 恢复十周年版被隐藏起来的作弊码。目前激活这些作弊码不会增加统计信息中的作弊次数。不区分大小写。无需在末尾输入中文说明。Restore the hidden cheat code of the 10th anniversary edition. Activating these cheats doesn't increase the times of cheats in the statistics for now. Case insensitive.

- TimeTraveler：时间前进4小时。Passes 4 hours immediately.
- SecretSpySet：武器包4，包含火神机枪、假YJ、夜视镜和热成像夜视镜。后两者交替出现。Weapon Pack 4, including Minigun, Vibrator, Night vision goggles and Thermal goggles. The latter two appear alternately.
- FreezeIt：锁定时间。游戏的阴影可能会出现问题。Freezes game time. Game's shadowing system may glitches.
- TrueGod：无敌，玩家不会受到任何伤害，除了游戏机制直接使玩家死亡的情况。God mode, player can't be damaged except death causes by game logic.
- NoPity：跳过（直接完成）当前任务，极少数任务不可跳过。Passes current mission (script bypass), except few missions.

#### 其他 Others
- `FixRadarIconInSeaGlitch`： 自动检测并修复CV（王氏车行）任务点和2个安全屋的图标在水中（地图中心）的bug，无需开新档。Automatically detects and fixes bugs in CV mission blips (Wang's Car) and two safe house blips in sea (map center) without starting a new game.
- `ColouredZoneNames`： 屏幕右下角显示地名时，还会显示帮派地盘的颜色。这是在原版游戏损坏的功能，原版只会在一个地盘由多个帮派控制时才显示。颜色计算方式类似于十周年版的JPatch（忽视帮派密度）而不是原版的SilentPatch（二次方变换）。When a place name is displayed in the bottom right corner of the screen, the color of the gang territory is also displayed. This was a broken feature in the vanilla game, which was only displayed when the turf was controlled by more than 1 gangs. The color calculation is similar to JPatch (ignoring gang density) for the 10th anniversary edition rather than SilentPatch (quadratic transformation) for the original PC edition.
- `SprintOnAnySurface`：在绝大多数室内空间可以冲刺。即原版和十周年的插件“Sprint Everywhere”。You can sprint in most interiors same as plugin "Sprint Everywhere" for the original and 10th anniversary edition.

### 3代 III
#### 自动保存 Auto Save
每隔一个特定的时间进行自动保存，而不像原来那样只在任务开始与完成时进行保存。保存到插槽sf9。
It can save your game every certain seconds instead of save only when you starts or passes a mission. It's will save to the slot called sf9.

- `Enabled`： 功能开启。
- `IntervalTime`： 间隔时间，以秒为单位，默认20秒，最低10秒。As name, in seconds. Default value is 20s, minimum value is 10s.

#### 显示FPS Show FPS
在屏幕左上角显示每秒帧数，根据数值，颜色会渐变变化，从红色到绿色。Frames per second is displayed in the upper left corner of the screen, and depending on the value, the color changes gradually, from red to green.

- `ShowFPS`： 功能开启。
- `MaxFPSToShowColor`： 显示为绿色的最小FPS值。The minimum FPS value to display in green.
- `UseModernFonts`： 是否显示字幕样式的字体，而不是用于标题的粗Pricedown字体。Whether to display a subtitle-style font instead of the bold Pricedown font used for titles.

#### 其他 Others
- `MafiaDontUseShotgun`：家族黑手党在游戏中后期使用AK47而不是霰弹枪，以降低难度。不影响任务“浓缩咖啡外卖！”与“血脉喷张”。Mafia Family is using AK47s instead of shotguns in late game to reduce difficulty. Do not affect the mission Espresso-2-Go! and Big'N'Veiny.
需在末尾输入中文说明。Restore the hidden cheat code of the 10th anniversary edition. Activating these cheats doesn't increase the times of cheats in the statistics for now. Case insensitive.

- TimeTraveler：时间前进4小时。Passes 4 hours immediately.
- SecretSpySet：武器包4，包含火神机枪、假YJ、夜视镜和热成像夜视镜。后两者交替出现。Weapon Pack 4, including Minigun, Vibrator, Night vision goggles and Thermal goggles. The latter two appear alternately.
- FreezeIt：锁定时间。游戏的阴影可能会出现问题。Freezes game time. Game's shadowing system may glitches.
- TrueGod：无敌，玩家不会受到任何伤害，除了游戏机制直接使玩家死亡的情况。God mode, player can't be damaged except death causes by game logic.
- NoPity：跳过（直接完成）当前任务，极少数任务不可跳过。Passes current mission (script bypass), except few missions.

#### 其他 Others
- `FixRadarIconInSeaGlitch`： 自动检测并修复CV（王氏车行）任务点和2个安全屋的图标在水中（地图中心）的bug，无需开新档。Automatically detects and fixes bugs in CV mission blips (Wang's Car) and two safe house blips in sea (map center) without starting a new game.
- `ColouredZoneNames`： 屏幕右下角显示地名时，还会显示帮派地盘的颜色。这是在原版游戏损坏的功能，原版只会在一个地盘由多个帮派控制时才显示。颜色计算方式类似于十周年版的JPatch（忽视帮派密度）而不是原版的SilentPatch（二次方变换）。When a place name is displayed in the bottom right corner of the screen, the color of the gang territory is also displayed. This was a broken feature in the vanilla game, which was only displayed when the turf was controlled by more than 1 gangs. The color calculation is similar to JPatch (ignoring gang density) for the 10th anniversary edition rather than SilentPatch (quadratic transformation) for the original PC edition.
- `SprintOnAnySurface`：在绝大多数室内空间可以冲刺。即原版和十周年的插件“Sprint Everywhere”。You can sprint in most interiors same as plugin "Sprint Everywhere" for the original and 10th anniversary edition.

### 3代 III
#### 自动保存 Auto Save
每隔一个特定的时间进行自动保存，而不像原来那样只在任务开始与完成时进行保存。保存到插槽sf9。
It can save your game every certain seconds instead of save only when you starts or passes a mission. It's will save to the slot called sf9.

- `Enabled`： 功能开启。
- `IntervalTime`： 间隔时间，以秒为单位，默认20秒，最低10秒。As name, in seconds. Default value is 20s, minimum value is 10s.

#### 显示FPS Show FPS
在屏幕左上角显示每秒帧数，根据数值，颜色会渐变变化，从红色到绿色。Frames per second is displayed in the upper left corner of the screen, and depending on the value, the color changes gradually, from red to green.

- `ShowFPS`： 功能开启。
- `MaxFPSToShowColor`： 显示为绿色的最小FPS值。The minimum FPS value to display in green.
- `UseModernFonts`： 是否显示字幕样式的字体，而不是用于标题的粗Pricedown字体。Whether to display a subtitle-style font instead of the bold Pricedown font used for titles.

#### 其他 Others
- `MafiaDontUseShotgun`：家族黑手党在游戏中后期使用AK47而不是霰弹枪，以降低难度。不影响任务“浓缩咖啡外卖！”与“血脉喷张”。Mafia Family is using AK47s instead of shotguns in late game to reduce difficulty. Do not affect the mission Espresso-2-Go! and Big'N'Veiny.
