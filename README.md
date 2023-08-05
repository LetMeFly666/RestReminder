# RestReminder

RestReminder(Pomodoro)：remind you to rest when you use computer too long. 休息提醒（番茄时钟）：使用电脑过久时提醒你休息

+ 项目地址：[Github@LetMeFly666/RestReminder](https://github.com/LetMeFly666/RestReminder)
+ 在线文档：[RestReminder.tisfy.eu.org](https://restreminder.tisfy.eu.org/)
+ 应用下载：[#发行版](#发行版)

## 使用介绍

启动后无窗口，只会在托盘区显示图标。

```worktime```（秒）后托盘区图标回冒泡提醒休息，提醒超过```work_timeout```未响应则会弹窗提醒。

休息时同理，对应提醒时间分别为```resttime```和```rest_timeout```。

修改配置文件（[conf.json](Settings/conf.json)）可以调整上述时长，可以右键托盘区图标修改```工作/休息```状态。

## 发行版

+ [v0.1-单文件版](https://github.com/LetMeFly666/RestReminder/releases/download/v0.1/v0.1-Win64-RestReminder.exe)
+ [v0.1-完整版](https://github.com/LetMeFly666/RestReminder/releases/download/v0.1/v0.1-Win64-RestReminder.zip)

## TODO:

- [ ] 暂停功能
- [ ] 图标的进度显示
- [ ] QTimer每秒1次并重绘 修改为 计算出下次需要更新的时间，则能极大程度上减少程序运算量
- [x] 若未点击弹出的提示框的确认按钮，直接右键切换工作状态了，则提示框应该被摧毁。
- [x] 若上条完成则此条自动完成。因为新弹出的提示框会显示在旧提示框下面，新的提示框不点击还无法点击旧的提示框。
- [x] QMessageBox弹出时QTimer停止计时了
