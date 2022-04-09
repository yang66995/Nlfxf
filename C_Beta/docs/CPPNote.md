<!--
 * @Author: your name
 * @Date: 2022-03-04 14:37:00
 * @LastEditTime: 2022-03-08 15:40:09
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \Nlfxf\nlfxf\nlfxf\CPPNote\CPPNote.md
-->

# C++ primer

## 变量和基本类型

#### 引用
```cpp
fun{
    int val = 1, qal = 2;
    int &val1 = val;//&val1代表引用
}
```

1. *引用*为*对象*提供了另一个名字。


- 避免野指针的出现，同时带来指针的便利。引用定义时必须初始化，且在进行初始化后就不会再改变了。 指针可以不用， 正常情况下需初始化为NULL，且指针的值在初始化后可以改变，即指向其它的存储单元。
- **引用是变量的别名，实际是指向变量存储的地址。**

#### 指针
```cpp
fun{
    int *b;
    float *c , d;//d是float类型对象，c是指向float类型指针
}
```

1. 指针是复合类型，实现了对其他*对象*的间接访问。指针与引用不同，本身就是一个*对象*，可以赋值和拷贝。
2. 指针定义可以不初始化，但在块作用域内定义的未初始化指针将和其他内置类型一样拥有**不确定**的值。

3. 获取对象的地址
- 指针存放某个对象的地址，要获取地址使用取址符（&）
```cpp
fun{
    int val = 1;
    int *p = &val;//p存放val的地址，或者说p是指向val指针
}
```

4. 指针类型通常要和它所指对象类型严格匹配。

5. 指针值（即地址）应属下列四种情况之一
- 指向一个对象
- 指向紧邻对象所占空间的下一个位置
- 空指针 0或null
- 无效指针，除上述情况外

4. 利用指针访问对象
- 如果指针指向了一个对象，则可对指针使用解引用符（*）访问该对象
   ```cpp
   fun{
       int val = 42;
       int *p = &val;
       cout <<*p; //符号 * 输出指针p所指对象的值42
   }
   ```
- 对指针解引用会得出所指的对象，对解引用的结果赋值，则就是给指针所指对象赋值。
```cpp   
   fun{
       *p = 0;
       cout << *p;//输出0，对 *p 赋值，实际就是对p所指对象赋值
   }
```
5. 空指针
```cpp
fun{
    int *p = nullptr;//c++11推荐
    int *p = 0;

    #include <cstdlib>
    int *p = NULL;
}
```
- 不指向任何对象
- 推荐使用nullptr

6. Void*指针
```cpp
fun{
    float obj = 3.14，*pd = &obj;
    void *pv = &obj;//obj类型任意
    pv = pd;
}
```
- 可以存放任意类型的对象地址，但对于该地址中的什么类型地址并不了解
- 无法直接操作void指针的对象，因为无法确定所指对象的类型

7. 指向指针的指针
```cpp
fun{
    int val = 100;
    int *p = &val;
    int **pp = &p;//pp是指向指针的指针
}
```
- 指针是内存中的对象，和其他一样，在内存中也有自己的地址。允许把指针的地址存放在另一个指针中
- 通过*数确定指针的级别
- 解引用指向指针的指针会**得到一个指针**

8. 指向指针的引用
```cpp
fun{
    int val = 100;
    int *p;
    int *&ral = p;//*说明ral引用的是一个指针

    ral = &val;
    *ral = 0;
    }
    ```
- 指针是对象，所指引用可以指向指针
- 引用不是对象，所以指针无法指向引用

#### Const限定符

1. Const创建后无法被更改
```cpp
fun{
    const int val = get_Vale();
    const int val = 777;
}
```
- const创建时必须初始化，但可以用任意复杂表达式初始化

2. const变量文件间共享

```c++
extern const int buffersize
```



