#include "queue.h"
#include <assert.h>

int main() {
    // Push, Pop, Front, Back
    {
        Queue<int> q;
        q.Push(1);
        q.Push(2);
        q.Push(3);
        q.Pop();
        assert(q.Front() == 2);
        assert(q.Back() == 3);

        q.Push(4);
        q.Pop();
        q.Pop();
        q.Push(5);
        q.Pop();
        assert(q.Front() == 5);
        assert(q.Back() == 5);
    }

    // Empty, Size, Clear
    {
        Queue<int> q;

        assert(q.Empty() == true);
        q.Push(1);
        q.Push(2);
        q.Push(10);
        assert(q.Size() == 3);
        assert(q.Front() == 1);
        assert(q.Empty() == false);

        q.Clear();
        q.Clear();
        assert(q.Empty() == true);

        q.Push(100);
        q.Clear();
        assert(q.Size() == 0);
    }

    // copy semantics
    {
        Queue<std::string> q1;
        q1.Push("abc");
        q1.Push("string");
        q1 = q1;

        Queue<std::string> q2;
        q2 = q1;
        assert(q2.Front() == "abc");

        Queue<std::string> q3 = q1;
        q3.Pop();
        assert(q3.Front() == "string");

        q1 = q2 = q3;
        q1.Pop();
        assert(q1.Empty() == true);
    }

    // move semantics
    {
        Queue<double> q1;
        double value = static_cast<double>(22) / static_cast<double>(7);

        q1.Push(3.14);
        q1.Push(value);
        q1 = std::move(q1);

        Queue<double> q2 = std::move(q1), q3;
        assert(q2.Size() == 2);
        assert(q2.Front() == 3.14);
        assert(q2.Back() == value);
        assert(q1.Empty() == true);

        q3 = std::move(q2);
        assert(q3.Size() == 2);
        assert(q3.Front() == 3.14);
        assert(q3.Back() == value);
        assert(q2.Empty() == true);
    }

    // Swap
    {
        int value = 10;
        Queue<int> q1;
        q1.Push(5);
        Queue<int> q2 = q1;
        q2.Push(value);

        assert(q1.Size() == 1);
        assert(q2.Size() == 2);

        q1.Swap(q2);

        assert(q1.Size() == 2);
        assert(q2.Size() == 1);
        assert(q1.Back() == value);
    }
}