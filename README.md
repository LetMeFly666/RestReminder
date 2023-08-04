# RestReminder

RestReminder(Pomodoro)：remind you to rest when you use computer too long. 休息提醒（番茄时钟）：使用电脑过久时提醒你休息

+ 项目地址：[Github@LetMeFly666/RestReminder](https://github.com/LetMeFly666/RestReminder)
+ 在线文档：[RestReminder.tisfy.eu.org](https://restreminder.tisfy.eu.org/)

## 使用介绍

启动后无窗口，只会在托盘区显示图标。

```worktime```（秒）后托盘区图标回冒泡提醒休息，提醒超过```work_timeout```未响应则会弹窗提醒。

休息时同理，对应提醒时间分别为```resttime```和```rest_timeout```。

修改配置文件（[conf.json](Settings/conf.json)）可以调整上述时长，可以右键托盘区图标修改```工作/休息```状态。

## TODO:

+ 暂停功能
+ 图标的进度显示
