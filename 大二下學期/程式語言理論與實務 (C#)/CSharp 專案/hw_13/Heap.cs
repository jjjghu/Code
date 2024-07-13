using System;
using System.Collections.Generic;

namespace hw_13
{
    public class Heap
    {
        private List<int> elementList; // 紀錄內容
        private bool isMaxHeap; // isMaxHeap = 1, maxHeap, else: minHeap

        public Heap(bool isMaxHeap = true)
        {
            this.elementList = new List<int>(); // 初始化
            this.isMaxHeap = isMaxHeap;
        }

        private int GetParentIndex(int index) => (index - 1) / 2;
        private int GetLeftChildIndex(int index) => 2 * index + 1;
        private int GetRightChildIndex(int index) => 2 * index + 2;

        private void Swap(int index1, int index2) // 輸入 index, 交換
        {
            int temp = elementList[index1];
            elementList[index1] = elementList[index2];
            elementList[index2] = temp;
        }

        public void Insert(int element) // 插入新節點, 開始 Heapify
        {
            elementList.Add(element);
            HeapifyUp(elementList.Count - 1);
        }

        public int Extract() // 獲取 root
        {
            if (elementList.Count == 0) // 空
                throw new InvalidOperationException("The heap is empty");

            int root = elementList[0];

            elementList[0] = elementList[elementList.Count - 1]; // 用最後一個節點取代 root, 開始 Heapify
            elementList.RemoveAt(elementList.Count - 1);
            HeapifyDown(0); // 往下挑戰

            return root;
        }

        private void HeapifyUp(int index) // 往上挑戰
        {
            // 挑戰到輸為止
            while (index > 0 && Compare(elementList[index], elementList[GetParentIndex(index)]))
            {
                // 挑戰成功, 交換
                Swap(index, GetParentIndex(index));
                // 繼續挑戰
                index = GetParentIndex(index);
            }
        }

        private void HeapifyDown(int index)
        {
            int lastIndex = elementList.Count - 1;

            while (index < lastIndex)
            {
                int leftChildIndex = GetLeftChildIndex(index);
                int rightChildIndex = GetRightChildIndex(index);
                int swapIndex = index;

                if (leftChildIndex <= lastIndex && Compare(elementList[leftChildIndex], elementList[swapIndex]))
                {
                    swapIndex = leftChildIndex;
                }

                if (rightChildIndex <= lastIndex && Compare(elementList[rightChildIndex], elementList[swapIndex]))
                {
                    swapIndex = rightChildIndex;
                }

                if (swapIndex == index)
                    break;

                Swap(index, swapIndex);
                index = swapIndex;
            }
        }

        private bool Compare(int first, int second) // 根據 isMaxHeap 決定比較方式
        {
            return isMaxHeap ? first > second : first < second;
        }
        public List<int> GetHeapList() // 輸出結果
        {
            return elementList;
        }
    }
}
