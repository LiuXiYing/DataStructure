#include <iostream>
#include <string>
#include "binTree.h"

/* 教师提供：本文件与 main 不得修改。
 *
 * 四个接口是学生的实现；核对整棵树时用 binTree.h 末尾教师提供的三种遍历
 * （Lab11 已经实现过，这里直接返回遍历序列）：先序序列加中序序列能唯一确定
 * 一棵二叉树，两条都对上，形状、元素、位置就全对；再用后序核对节点个数。
 *
 * 本次只用 char，建树统一用先序扩展序列：“每个字符是一个元素，'#' 表示空子树”。
 */

/* 元素 e 是否存在，并且命中节点确实保存了 e。 */
bool has(BinTree& tree, char e) {
    BinNodePosi x = tree.search(e);
    if (x == nullptr) {
        return false;
    }
    return x->data == e;
}

/* 整棵树是否正好是 pre / in 给定的先序与中序，且节点个数与 pre 等长。
 * 先序加中序唯一确定一棵二叉树，所以这两条对上就说明形状、元素、位置全对。 */
bool shapeIs(BinTree& tree, const std::string& pre, const std::string& in) {
    if (travPre(tree.root()) != pre) {
        return false;
    }
    if (travIn(tree.root()) != in) {
        return false;
    }
    return travPost(tree.root()).size() == pre.size();
}

/* 打印单组结果并返回判断值，让 main 能累计通过的组数。 */
bool check(const char* name, bool ok) {
    std::cout << name << ": " << (ok ? "PASS" : "FAIL") << '\n';
    return ok;
}

/* 以下测试与 main 由教师提供，不得修改。 */
int main() {
    int passed = 0;

    /* 第 1 组：空树——空串建出的是一棵空树 */
    BinTree E;
    bool builtEmpty = E.build("");
    bool emptyTree = builtEmpty && (E.root() == nullptr) && (E.search('A') == nullptr);
    emptyTree = emptyTree && shapeIs(E, "", "");
    if (check("empty tree", emptyTree)) {
        ++passed;
    }

    /* 第 2 组：建一棵只有一个节点的树，根是叶子 */
    BinTree R;
    bool builtOne = R.build("A##");
    BinNodePosi r = R.root();
    bool rootOk = builtOne && (r != nullptr) && (r->data == 'A') && IsLeaf(*r);
    rootOk = rootOk && shapeIs(R, "A", "A");
    if (check("build root", rootOk)) {
        ++passed;
    }

    /* 第 3 组：按先序扩展序列建出指定形状，并确认非空树上不能再次建树。
     * "ABD##E##C#F##" 对应：
     *          A
     *         / \
     *        B   C
     *       / \    \
     *      D   E    F
     */
    BinTree T;
    bool builtShape = T.build("ABD##E##C#F##");
    bool shapeOk = builtShape && shapeIs(T, "ABDECF", "DBEACF");
    bool rebuildRejected = !T.build("A##");           /* 已有树，必须拒绝 */
    shapeOk = shapeOk && rebuildRejected && shapeIs(T, "ABDECF", "DBEACF");
    if (check("build shape", shapeOk)) {
        ++passed;
    }

    /* 第 4 组：查找命中——六个元素都能查到，且节点确实保存了该元素 */
    bool hits = has(T, 'A') && has(T, 'B') && has(T, 'D')
                && has(T, 'E') && has(T, 'C') && has(T, 'F');
    if (check("search hits", hits)) {
        ++passed;
    }

    /* 第 5 组：查找落空——树中没有的元素返回空槽 */
    bool misses = (T.search('X') == nullptr) && (T.search('Z') == nullptr)
                  && (T.search('#') == nullptr);
    if (check("search misses", misses)) {
        ++passed;
    }

    /* 第 6 组：删除叶子——D 没有孩子，删掉后 B 的左孩子变为空 */
    bool leafRemoved = T.remove('D');
    bool leafGone = leafRemoved && !has(T, 'D') && shapeIs(T, "ABECF", "BEACF");
    if (check("remove leaf", leafGone)) {
        ++passed;
    }

    /* 第 7 组：删除非叶子——B 还有右孩子 E，拒绝删除且树保持不变 */
    bool nonLeafRejected = !T.remove('B');
    bool keptAfterReject = nonLeafRejected && has(T, 'B') && shapeIs(T, "ABECF", "BEACF");
    if (check("remove non-leaf", keptAfterReject)) {
        ++passed;
    }

    /* 第 8 组：删除根节点——根是叶子（只有一个节点）时，删完变成空树 */
    BinTree S;
    bool soloBuilt = S.build("M##");
    bool soloRemoved = S.remove('M');
    bool soloEmpty = soloBuilt && soloRemoved && (S.root() == nullptr) && shapeIs(S, "", "");
    if (check("remove root", soloEmpty)) {
        ++passed;
    }

    /* 第 9 组：删除不存在的元素——不改变树 */
    bool missingRejected = !T.remove('Q');
    bool unchangedAfterMissing = missingRejected && shapeIs(T, "ABECF", "BEACF");
    if (check("remove missing", unchangedAfterMissing)) {
        ++passed;
    }

    /* 第 10 组：修改——把叶子 E 的值改成 K，节点本身不动，只换 data */
    BinNodePosi eNode = T.search('E');
    bool updated = T.update('E', 'K');
    bool sameNode = (T.search('K') == eNode);      /* 原地改：还是原来那个节点 */
    bool updateOk = updated && !has(T, 'E') && sameNode && shapeIs(T, "ABKCF", "BKACF");
    if (check("update", updateOk)) {
        ++passed;
    }

    /* 第 11 组：三种不该修改的情形——值相同、旧值不存在、新值已存在，都不动树 */
    bool sameValue = !T.update('K', 'K');
    bool oldMissing = !T.update('Z', 'Y');
    bool newExists = !T.update('K', 'A');
    bool treeKept = has(T, 'K') && has(T, 'A') && shapeIs(T, "ABKCF", "BKACF");
    if (check("update rejected", sameValue && oldMissing && newExists && treeKept)) {
        ++passed;
    }

    /* 第 12 组：删空之后可以重新建树——_root 必须真的回到 nullptr */
    BinTree U;
    bool u1 = U.build("M##");
    bool u2 = U.remove('M');                     /* 唯一节点，删完是空树 */
    bool u3 = U.build("AB##C##");                /* 空树：允许再建一次 */
    bool rebuilt = u1 && u2 && u3 && (U.search('M') == nullptr) && shapeIs(U, "ABC", "BAC");
    if (check("rebuild", rebuilt)) {
        ++passed;
    }

    std::cout << "tree tests: " << passed << "/12 passed\n";
    return passed == 12 ? 0 : 1;     /* 退出码供 CTest 判断整个目标是否通过 */
}
