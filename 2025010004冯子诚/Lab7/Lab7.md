# Lab7：从 Lab6 的 C 链表到课本版 List<T>

## 一、配置 CMakeLists.txt
（已根据作业要求配置，见 CMakeLists.txt 文件）

## 二、完成本次作业所需的新知识
（已理解相关概念）

## 三、三个文件：必须使用的框架与要补的代码
（已完成编写，见 listNode.h、list.h、main.cpp 文件）

## 四、选择题与填空

### 4.1 双向链表的结点与两个哨兵
- [x] A. 多出来的是 `pred`；`succ` 就是 Lab6 的 `next` 改了名字，两个哨兵让表头、表尾的处理完全对称，`insertAsLast` 变成 `O(1)`

### 4.2 接链三句的顺序
- [x] C. 第二句先跑，`pred` 已经变成 `x`，第一句等于执行 `x->succ = x`，新结点自己指向自己；输出打到 `[size = 5]` 就停住，紧接着退出码 139

### 4.3 删除结点为什么不用找前驱
- [x] A. 因为 `pred` 直接存着前驱；两句断链都只读 `p->pred`、`p->succ`，谁都不去改它们，所以能颠倒。而接链的第二句恰好改掉第一句要读的 `pred`，所以不能颠倒——判据是同一条：后一句会不会改掉前一句要读的成员

### 4.4 `template` 那一行的作用范围
- [x] B. 这一行只管紧跟它的那一个定义，下一个定义要重新写；类外定义必须写成"`template <typename T>` 一行 + 名字里的 `List<T>::`"，少一样都编不过

### 4.5 模板的定义为什么必须写在头文件里
- [x] B. 每个文件单独编译都能通过，最后链接时报 `Undefined symbols`，因为编译器看不见完整的模板定义，就不会为 `List<int>` 生成 `print()` 的代码

### 4.6 `private` / `protected` 的作用
- [x] B. 编译器真的会拦：类外面的代码写 `list.header` 或 `list._size` 直接编译不过（C 版只能靠注释提醒）；而 `protected` 允许自己以及将来继承 `List` 的派生类调用，用 `List` 的人不需要也不该直接调

### 4.7 填空：C 版与课本版逐条对照

| Lab6 的 C 版 | 本次的课本版 |
| :--- | :--- |
| `LinkedList list; listInit(&list);` | `List<int> list;`（构造函数自动调用 init） |
| `listPushBack(&list, v)` | `list.insertAsLast(v)` |
| `listInsert(&list, 2, 25)` | `list.insert(2, 25)` |
| `listRemove(&list, 1, &removed)` | `list.remove(1, removed)` |
| `listFind(&list, 18)`（返回秩） | `list.rankOf(list.find(18))` |
| `main` 结尾的 `listDestroy(&list);` | 不用写（析构函数自动调用） |

### 4.8 填空：三句话解释
用三到五句话回答：为什么模板的成员函数定义必须写在头文件里，而不能像普通函数那样"声明放 `.h`、定义放 `.cpp`"？把代码拆成 `listNode.h` 与 `list.h` 两个文件，又解决了什么？

> 模板是编译期的模子：编译器只有看到完整的函数体（定义），才能在实例化 `List<int>` 时生成对应的 `int` 版代码；若定义放在 `.cpp`，编译其他文件时看不见定义，链接阶段就会报 `Undefined symbols`。把结点与表拆成 `listNode.h` 和 `list.h`，一是隔离了改动频率不同的两层（结点更底层、通用），二是让模板定义保持在头文件里、仍能模块化组织，避免几百行塞进单文件。

---

## 五、提交要求
（已按要求整理文件）

---