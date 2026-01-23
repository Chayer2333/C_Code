#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构
struct ListNode {
    int data;
    struct ListNode* next;
};

// 创建新节点
struct ListNode* createNode(int data) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (newNode == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 在链表末尾添加节点
void appendNode(struct ListNode** head, int data) {
    struct ListNode* newNode = createNode(data);
    
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    
    struct ListNode* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// 打印链表
void printList(struct ListNode* head) {
    struct ListNode* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// 倒置链表数据域（方法1：使用数组存储数据）
void reverseDataMethod1(struct ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return; // 空链表或只有一个节点，无需处理
    }
    
    // 计算链表长度
    int length = 0;
    struct ListNode* temp = head;
    while (temp != NULL) {
        length++;
        temp = temp->next;
    }
    
    // 创建数组存储数据
    int* dataArray = (int*)malloc(length * sizeof(int));
    if (dataArray == NULL) {
        printf("内存分配失败\n");
        return;
    }
    
    // 将链表数据存入数组
    temp = head;
    int i;
    for (i = 0; i < length; i++) {
        dataArray[i] = temp->data;
        temp = temp->next;
    }
    
    // 将数组倒序数据写回链表
    temp = head;
    for (i = length - 1; i >= 0; i--) {
        temp->data = dataArray[i];
        temp = temp->next;
    }
    
    free(dataArray);
}

// 倒置链表数据域（方法2：递归方法）
void reverseDataRecursive(struct ListNode* head, struct ListNode** current, int* index) {
    if (head == NULL) {
        return;
    }
    
    // 递归到链表末尾
    reverseDataRecursive(head->next, current, index);
    
    // 交换数据
    if (*current != NULL && (*index)-- > 0) {
        int temp = head->data;
        head->data = (*current)->data;
        (*current)->data = temp;
        *current = (*current)->next;
    }
}

void reverseDataMethod2(struct ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return;
    }
    
    struct ListNode* current = head;
    int length = 0;
    struct ListNode* temp = head;
    while (temp != NULL) {
        length++;
        temp = temp->next;
    }
    
    reverseDataRecursive(head, &current, &length);
}

// 倒置链表数据域（方法3：双指针方法）
void reverseDataMethod3(struct ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return;
    }
    
    // 计算链表长度
    int length = 0;
    struct ListNode* temp = head;
    while (temp != NULL) {
        length++;
        temp = temp->next;
    }
    
    // 使用双指针交换数据
    struct ListNode* left = head;
    int i,j;
    for (i = 0; i < length / 2; i++) {
        struct ListNode* right = head;
        // 移动右指针到对称位置
        for (j = 0; j < length - i - 1; j++) {
            right = right->next;
        }
        
        // 交换数据
        int tempData = left->data;
        left->data = right->data;
        right->data = tempData;
        
        left = left->next;
    }
}

// 释放链表内存
void freeList(struct ListNode* head) {
    struct ListNode* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct ListNode* head = NULL;
    
    // 创建测试链表
    printf("创建链表:\n");
    int i;
    for (i = 1; i <= 6; i++) {
        appendNode(&head, i);
    }
    printList(head);
    
    // 使用方法1倒置数据域
    printf("\n使用方法1倒置数据域:\n");
    reverseDataMethod1(head);
    printList(head);
    
    // 使用方法2倒置数据域（再次倒置，恢复原状）
    printf("\n使用方法2倒置数据域:\n");
    reverseDataMethod2(head);
    printList(head);
    
    // 使用方法3倒置数据域（再次倒置，恢复原状）
    printf("\n使用方法3倒置数据域:\n");
    reverseDataMethod3(head);
    printList(head);
    
    // 测试空链表
    printf("\n测试空链表:\n");
    struct ListNode* emptyList = NULL;
    reverseDataMethod1(emptyList);
    printList(emptyList);
    
    // 测试单节点链表
    printf("\n测试单节点链表:\n");
    struct ListNode* singleNodeList = createNode(42);
    printList(singleNodeList);
    reverseDataMethod1(singleNodeList);
    printList(singleNodeList);
    
    // 释放内存
    freeList(head);
    freeList(singleNodeList);
    
    return 0;
}
