# Lab7 书面题

## 四、选择题与填空

### 4.1 双向链表的结点与两个哨兵

- [x] A. 多出来的是 pred；succ 就是 Lab6 的 next 改了名字，两个哨兵让表头、表尾的处理完全对称，insertAsLast 变成 O(1)
- [ ] B. 多出来的是两个哨兵指针，各占 4 字节
- [ ] C. int data 从 4 字节变成了 12 字节
- [ ] D. pred、succ 各占 4 字节，构造函数再占 8 字节

### 4.2 接链三句的顺序

- [ ] A. 编译错误
- [ ] B. 两句互不影响，结果一样
- [x] C. 第二句先跑，pred 已经变成 x，第一句等于执行 x->succ = x，新结点自己指向自己；输出打到 [size = 5] 就停住，紧接着退出码 139
- [ ] D. 新结点被插到了表头

### 4.3 删除结点为什么不用找前驱

- [x] A. 因为 pred 直接存着前驱；两句断链都只读 p->pred、p->succ，谁都不去改它们，所以能颠倒。而接链的第二句恰好改掉第一句要读的 pred，所以不能颠倒——判据是同一条：后一句会不会改掉前一句要读的成员
- [ ] B. 因为断链改的是指针，接链改的是数据
- [ ] C. 因为 delete 只能写在最后一句
- [ ] D. 其实两处都不能颠倒，只是断链写反了不容易被发现

### 4.4 template 那一行的作用范围

- [ ] A. 这是语法装饰，写不写都能编过
- [x] B. 这一行只管紧跟它的那一个定义，下一个定义要重新写；类外定义必须写成"template <typename T> 一行 + 名字里的 List<T>::"，少一样都编不过
- [ ] C. 写一次就够，重复写只是为了排版
- [ ] D. 因为文件里有两个模板，所以每段代码都要写一行

### 4.5 模板的定义为什么必须写在头文件里

- [ ] A. 编译就报错，因为 .cpp 里看不到模板参数
- [x] B. 每个文件单独编译都能通过，最后链接时报 Undefined symbols，因为编译器看不见完整的模板定义，就不会为 List<int> 生成 print() 的代码
- [ ] C. 一切正常，和普通类完全一样
- [ ] D. 可以编译运行，只在调用 print() 时抛异常

### 4.6 private / protected 的作用

- [ ] A. 只是注释里的约定，编译器仍然不管
- [x] B. 编译器真的会拦：类外面的代码写 list.header 或 list._size 直接编译不过（C 版只能靠注释提醒）；而 protected 允许自己以及将来继承 List 的派生类调用，用 List 的人不需要也不该直接调
- [ ] C. protected 下的函数执行更快
- [ ] D. 对象占的内存会变少

### 4.7 填空：C 版与课本版逐条对照

| Lab6 的 C 版 | 本次的课本版 |
| :--- | :--- |
| `LinkedList list; listInit(&list);` | `List<int> list;` |
| `listPushBack(&list, v)` | `list.insertAsLast(v)` |
| `listInsert(&list, 2, 25)` | `list.insert(2, 25)` |
| `listRemove(&list, 1, &removed)` | `list.remove(1, removed)` |
| `listFind(&list, 18)`（返回秩） | `list.rankOf(list.find(18))` |
| `main` 结尾的 `listDestroy(&list);` | 不用写，析构函数自动跑 |

### 4.8 填空：三句话解释

> 模板是编译期的模子，编译器必须先看见完整的定义，才能在写 `List<int>` 时生成 int 版的代码。如果定义放在 `.cpp` 里，编译 `main.cpp` 时只看到声明，编译器不会为 `List<int>::print()` 生成代码，最后链接时报 `Undefined symbols`。把代码拆成 `listNode.h` 和 `list.h`，是因为结点是通用构件、改动少，`List` 会持续增长，两者职责不同；同时模板定义必须整体在头文件里，拆开后几百行也不会挤在一个文件中。