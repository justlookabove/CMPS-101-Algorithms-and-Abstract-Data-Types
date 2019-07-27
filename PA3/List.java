/* ************************************************************************
*                                                                         *
*                   Kiran Gunasekaran, kgunase@ucsc.edu                   *
*                                                                         *
*                              CMPS 101: PA1                              *
*                                                                         *
*                             November 5, 2017                            *
*                                                                         *
*  _____________________________________________________________________  *
*                                                                         *
*                                List.java                                *
*                                                                         *
**************************************************************************/

// package thisoneguy;

public class List {
    private class Node {
        public Node prev, next;
        Object value;

        public Node(Object value, Node prev, Node next) {
            this.value = value;
            this.prev = prev;
            this.next = next;
        }

        public Node(Object value) {
            this(value, null, null);
        }
    }

    // Fields
    private Node head, tail, cursor;
    private int length, index;

    // Constructor
    public List() {
        clear();
    }

/* ************************************************************************
*                                                                         *
*                            Access functions                             *
*                                                                         *
**************************************************************************/

    // Returns the number of elements in this list.
    public int length() {
        return length;
    }

    // Returns front element. Pre: length() > 0.
    public Object front() {
        if (length < 0) {
            throw new IllegalStateException("ERROR: front() is being" +
                " called on an empty List");
        } else {
            return head.value;
        }
    }

    // Returns back element. Pre: length()>0.
    public Object back() {
        if (length < 0) {
            throw new IllegalStateException("ERROR: back() is being" +
                " called on an empty List");
        }
        return tail.value;
    }

    // Returns cursor element. Pre: length()>0, index()>=0.
    public Object get() {
        if (length <= 0) {
            throw new IllegalStateException("ERROR: get() is being" +
                " called on an empty List");
        }
        if (index < 0) {
            throw new IllegalStateException("ERROR: get() is called" +
                " with an undefined index on List");
        } else
            return cursor.value;
    }

    // If cursor is defined, returns the index of the cursor element,
    // otherwise returns -1.
    public int index() {
        if (cursor == null) {
            index = -1;
        }
        return index;
    }


    // Returns true if and only if this List and L are the same
    // integer sequence. The states of the cursors in the two Lists
    // are not used in determining equality
    boolean equals(List L) {
        if (L == null)
            return false;

        return toString().equals(L.toString());
    }

/* ************************************************************************
*                                                                         *
*                         Manipulation procedures                         *
*                                                                         *
**************************************************************************/

    // Resets this List to its original empty state.
    public void clear() {
        head = null;
        tail = null;
        cursor = null;
        length = 0;
        index = -1;
    }

    // If List is non-empty, places the cursor under the front element,
    // otherwise does nothing.
    public void moveFront() {
        if (length != 0) {
            cursor = head;
            index = 0;
        }
    }

    // If List is non-empty, places the cursor under the back element,
    // otherwise does nothing.
    public void moveBack() {
        if (length != 0) {
            cursor = tail;
            index = length() - 1;
        }
    }

    // If cursor is defined and not at front, moves cursor one step toward
    // front of this List, if cursor is defined and at front, cursor becomes
    // undefined, if cursor is undefined does nothing.
    public void movePrev() {
        if (cursor != null) {
            if (cursor == head) {
                cursor = null;
            } else {
                cursor = cursor.prev;
                index--;
            }
        }
    }

    // If cursor is defined and not at back, moves cursor one step toward 
    // back of this List, if cursor is defined and at back, cursor becomes 
    // undefined, if cursor is undefined does nothing.
    void moveNext() {
        if (cursor != null) {
            if (cursor == tail) {
                cursor = null;
            } else {
                cursor = cursor.next;
                index++;
            }
        }
    }

    // Insert new element into this List. If List is non-empty,
    // insertion takes place before front element.
    void prepend(Object data) {
        Node node = new Node(data);

        if (length() == 0) {
            head = node;
            tail = node;
        } else {
            head.prev = node;
            node.next = head;
            head = node;
            index++;
        }
        length++;
    }

    // Insert new element into this List. If List is non-empty,
    // insertion takes place after back element.
    void append(Object data) {
        Node node = new Node(data);

        if (length() == 0) {
            head = node;
            tail = node;
        } else {
            tail.next = node;
            node.prev = tail;
            tail = node;
        }
        length++;
    }

    // Insert new element before cursor.
    // Pre: length()>0, index()>=0.
    void insertBefore(Object data) {
        if (length <= 0 || index < 0) {
            throw new IllegalStateException("ERROR: List should not be empty");
        }

        if (index == 0) {
            prepend(data);
            return;
        }

        Node node = new Node(data, cursor.prev, cursor);
        cursor.prev = node;
        node.prev.next = node;
        cursor = node.next;
        length++;
        index++;
    }

    // Inserts new element after cursor.
    // Pre: length()>0, index()>=0.
    void insertAfter(Object data) {
        if (length <= 0 || index < 0) {
            throw new IllegalStateException("ERROR: List should be non empty");
        }
        if (index() == length() - 1) {
            append(data);
            return;
        }

        Node node = new Node(data, cursor.next, cursor);
        cursor.next = node;
        node.next.prev = node;
        length++;
    }

    // Deletes the front element. Pre: length()>0.
    void deleteFront() {
        if (length <= 0) {
            throw new IllegalStateException("ERROR: deleteFront() is " +
                "called on a empty list");
        }

        if (cursor == head) {
            cursor = null;
            index = -1;
        }
        index--;

        head = head.next;
        if (head != null)
            head.prev = null;
        length--;

    }

    // Deletes the back element. Pre: length()>0.
    void deleteBack() {
        if (length <= 0) {
            throw new IllegalStateException("deleteBack() is called on a " +
                "empty list");
        }

        if (cursor == tail) {
            cursor = null;
            index = -1;
        }
        tail = tail.prev;
        if (tail != null)
            tail.next = null;
        length--;

    }

    // Deletes cursor element, making cursor undefined.
    // Pre: length()>0, index()>=0.
    void delete() {
        if (length <= 0) {
            throw new IllegalStateException("List should be non-empty");
        }

        if (index < 0) {
            throw new IllegalStateException("Cursor should be defined");
        }
        if (cursor == head) {
            deleteFront();
        } else if (cursor == tail) {
            deleteBack();
        } else {
            cursor.prev.next = cursor.next;
            cursor.next.prev = cursor.prev;
            cursor = null;
            length--;
            index = -1;
        }
    }

/* ************************************************************************
*                                                                         *
*                              Other Methods                              *
*                                                                         *
**************************************************************************/

    // Overrides Object's to String method. Returns a String
    // representation of this List consisting of a space
    // separated sequence of integers, with front on left.
    public String toString() {
        String toString = "";
        Node node = head;
        if (this.length != 0) {
            while (node.next != null) {
                // toString = toString + String.valueOf(node.value) + " ";
                toString = toString + node.value + " ";
                node = node.next;
            }
            toString = toString + node.value;
        }
        return toString;
    }

    // Returns a new List representing the same integer sequence as this
    // List. The cursor in the new list is undefined, regardless of the
    // state of the cursor in this List. This List is unchanged.
    List copy() {
        List copy = new List();
        Node i = head;
        while (i != null) {
            copy.append(i.value);
            i = i.next;
        }
        return copy;
    }
}