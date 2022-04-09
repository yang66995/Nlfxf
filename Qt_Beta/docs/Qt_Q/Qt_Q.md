<!--

 * @Author: yang66995
 * @Date: 2020-09-01 21:13:37
 * @LastEditTime: 2020-09-02 20:31:09
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \yang66995\qt_dev\docs\Qt_Q.md
-->

# Qt调试问题

## Qt控制时间精度

1、**enum Qt::TimerType**

The timer type indicates how accurate a timer can be.

| Constant            | Value | Description                                                          |
| ------------------- | ----- | -------------------------------------------------------------------- |
| Qt::PreciseTimer    | 0     | Precise timers try to keep millisecond accuracy                      |
| Qt::CoarseTimer     | 1     | Coarse timers try to keep accuracy within 5% of the desired interval |
| Qt::VeryCoarseTimer | 2     | Very coarse timers only keep full second accuracy                    |

On UNIX (including Linux, macOS, and iOS), Qt will keep millisecond accuracy for Qt::PreciseTimer. For Qt::CoarseTimer, the interval will be adjusted up to 5% to align the timer with other timers that are expected to fire at or around the same time. The objective is to make most timers wake up at the same time, thereby reducing CPU wakeups and power consumption.
On Windows, Qt will use Windows's Multimedia timer facility (if available) for Qt::PreciseTimer and normal Windows timers for Qt::CoarseTimer and Qt::VeryCoarseTimer.
On all platforms, the interval for Qt::VeryCoarseTimer is rounded to the nearest full second (e.g. an interval of 23500ms will be rounded to 24000ms, and 20300ms to 20000ms).

```c++
    //程序启动后 自动开始定时发送串口指令帧 周期为PERIOD
    TimerSendInit = new QTimer(this);
    connect(TimerSendInit, SIGNAL(timeout()), this, SLOT(OnTimerSendInit()));
    TimerSendInit->setTimerType(Qt::PreciseTimer); // 尽可能保证定时器毫秒精度
    TimerSendInit->start(PERIOD);

```

发送80ms，未添加`TimerSendInit->setTimerType(Qt::PreciseTimer);`前，示波器实测92ms，添加后测试为80ms。

## QByteArray to quint16

```Qt
QDataStream dataStream(yourByteArray);
quint16 foo;
dataStream >> foo;
```

## 提取QByteArray中的字节

### mid()

**QByteArray** QByteArray::**mid**(**int** *pos*, **int** *len* = -1) const

Returns a byte array containing *len* bytes from this byte array, starting at position *pos*.

If *len* is -1 (the default), or *pos* + *len* >= [size](qbytearray.html#size)(), returns a byte array containing all bytes starting at position *pos* until the end of the byte array.

Example:

```cpp

  QByteArray x("Five pineapples");
  QByteArray y = x.mid(5, 4);     // y == "pine"
  QByteArray z = x.mid(5);        // z == "pineapples"

```

See also [left](qbytearray.html#left)() and [right](qbytearray.html#right)().

### left()

**QByteArray** QByteArray::**left**(**int** *len*) const

Returns a byte array that contains the leftmost *len* bytes of this byte array.

The entire byte array is returned if *len* is greater than size().

Example:

```cpp

  QByteArray x("Pineapple");
  QByteArray y = x.left(4);
  // y == "Pine"
```

### right()

**QByteArray** QByteArray::**right**(**int** *len*) const

Returns a byte array that contains the rightmost *len* bytes of this byte array.

The entire byte array is returned if *len* is greater than size().

Example:

```cpp

  QByteArray x("Pineapple");
  QByteArray y = x.right(5);
  // y == "apple"
```

## Qt中数据类型定义

| Qt数据类型 | 等效定义               | 字节数 |
| ---------- | ---------------------- | ------ |
| qint8      | signed char            | 1      |
| qint16     | signed short           | 2      |
| qint32     | signed int             | 4      |
| qint64     | long long int          | 8      |
| qlonglong  | long long int          | 8      |
| quint8     | unsigned char          | 1      |
| quint16    | unsigned short         | 2      |
| quint32    | unsigned int           | 4      |
| quint64    | unsigned long long int | 8      |
| qulonglong | unsigned long long int | 8      |
| uchar      | unsigned char          | 1      |
| ushort     | unsigned short         | 2      |
| uint       | unsigned int           | 4      |
| ulong      | unsigned long          | 8      |
| qreal      | double                 | 8      |
| qfloat16   |                        | 2      |

qfloat16是Qt中新增的一个类，用于表示16位浮点数，需包含类`<QFloat16>`。

## 串口接收缓冲区问题

缓冲区设置问题导致串口收数时几秒钟后无法再继续工作，422转USB指示灯同步停止闪烁，使用串口助手显示正常。
```cpp
void QSerialPort::setReadBufferSize(qint64 size);
  
Sets the size of QSerialPort's internal read buffer to be size bytes.
If the buffer size is limited to a certain size, QSerialPort will not buffer more than this size of data. The special case of a buffer size of 0 means that the read buffer is unlimited and all incoming data is buffered. This is the default.
This option is useful if the data is only read at certain points in time (for instance in a real-time streaming application) or if the serial port should be protected against receiving too much data, which may eventually cause the application to run out of memory.

See also readBufferSize() and read().
```
```cpp
mySerialPort->setReadBufferSize(4096);//设置串口缓冲区大小 根据实际工程需要设定
    /*XXX项目 串口发送20ms一次，一帧长度128个字节; 接收最快40ms一次，帧长度不超过60字节，这里1024空间足够*/
    //测试发现每次只接收到512字节，会把长字节分成几个512？512似乎是串口通信缓冲区的默认大小。由于影响不大，这个问题暂时搁置一下
​```cpp
```

## 基于互斥量的线程同步

QMutex和QMutexLocker，基于互斥量的线程同步类。

lock()：锁定互斥量。如果一个线程锁定了则个互斥量，它将阻塞执行到其他线程解锁这个互斥量。

unlock()：解锁互斥量，与lock()配对使用。

tryLock()：试图锁定一个互斥量，成功返回true，如果其他线程以及那个锁定了这个互斥量，则返回false，不阻塞程序。

```cpp

bool MainWindow::Webclose()//关闭网口接收线程 释放网口和线程资源 包括网口接收线程、网口数据保存线程、网口各类数据解压显示线程
{
    if (ui->checkBox_RecordWeb->isChecked())//说明文件尚未关闭
    {
        ui->checkBox_RecordWeb->setChecked(false);    //这样触发才对 原来的方法:on_checkBox_RecordWeb_toggled(false);是错误的！
    }
    //关闭网口
    CloseSocket_signal();
    
    //其他线程中可能有使用了lock()的情况发生，此时关闭网口接收线程执行至此lock()时将会阻塞程序，直至其他线程中unlock()位置，保护防止网口保存文件等操作还未完成。
    mutex_forCloseUdpSocket.lock();//阻塞程序，等待网口关闭后继续执行
    mutex_forCloseUdpSocket.unlock();
    
    
    threadWebRec->quit();//退出网口接收线程的事件循环
    threadWebRec->wait();//等待线程threadWebRec运行结束  阻塞主线程
    return true;//false保护？
}
```





```cpp
memcpy(SEI_Array.data(),OneP1024_ABC.data()+6,SEI_LENTH);
```

.data()??????指针   +6  指针位置挪6个？



```cpp
                                    memcpy(h264_Array_nohead.data(),OneP1024_ABC.data()+6,LENGTH_PACKET_1016);//存入1016个字节的数据（去掉头尾后的）

```

尾巴咋去掉的？



## udpsocket

程序输出`QNativeSocketEngine::bind() was not called in QAbstractSocket::UnconnectedState`，





3.问题三：调用connectToHost建立连接后调用write发送数据失败

错误描述：QNativeSocketEngine::write() was not called in QAbstractSocket::ConnectedState

**问题描述：错误为不是在QTcpSocket连接状态下调用write()函数，即调用write()时连接尚未建立**

问题解决：方法一，在调用connectToHost后接着调用waitForConnected(timeout)，并给延时参数赋值，之后在调用write()函数；

​       方法二，在信号connected的槽函数里调用write()函数进行数据发送；

​       方法三，在信号stateChangeed的槽函数内判断当前QTcpSocket对象连接状态state()，如果是QAbstractSocket::ConnectedState则调用write()函数进行数据发送；

实际是使用一个连接标志位来决定是否调用write()函数发送数据，在信号connected的槽函数里修改标志位为真，每次定时器到期都首先判断标志位，为假则重新尝试建立连接。

me：建议方法一方法三结合使用。stateChangeed信号在网线断开的时候有个大概20s的延时，在这20s内socket连接还是在的。这个需要注意。





```cpp
    if(ZHUdpSocket->state())
    {
        writelog("指令帧下发网口ZHUdpsocket打开成功");
        ZHUdpSocket->writeDatagram(ByteArray_SePort_Send, QHostAddress::Broadcast, 6004); //测试用

    }
    else
    {
        writeError("指令帧下发网口ZHUdpsocket打开失败");
    }

```



\1. 同一个Socket只可以将1个端口绑定到1个地址上。
\2. 即使不同的Socket也不能重复绑定相同的地址和端口。
\3. 不同的Socket可以将不同的端口绑定到相同的IP地址上。
\4. 不同的Socket可以将相同的端口绑定到不同的IP地址上。





## 随意发送帧导致程序闪退

ASSERT: "uint(i) < uint(size())" in file [C:\Qt\Qt5.9.6\5.9.6\mingw53_32\include/QtCore/qbytearray.h, line 467](C:\Qt\Qt5.9.6\5.9.6\mingw53_32\include/QtCore/qbytearray.h, line 467)

E:/Projects/YJC66995/build-YJCv2-Desktop_Qt_5_9_6_MinGW_32bit-Debug/debug/YJC.exe exited with code 3



发送帧 HEX 68 74 74 



## 去掉数据头尾

```cpp
 memcpy(h264_Array_nohead.data(),OneP1024_ABC.data()+6,LENGTH_PACKET_1016);//存入1016个字节的数据（去掉头尾后的）
```



## socket问题

当使用ZHUdpsocket writeDatagrame时，代码中使用两次判断`if(ZHUdpsocket->stable() == 4);` 时，正常收图传数据的`udpsockst`就会无法收到数据



## yjc

、1、保存网口数据文件的线程是`myudprecsavetofile`;考虑将UDP回报帧的数据在此线程进行保存。