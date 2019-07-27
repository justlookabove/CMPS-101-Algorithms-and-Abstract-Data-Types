/* ************************************************************************
*                                                                         *
*                   Kiran Gunasekaran, kgunase@ucsc.edu                   *
*                                                                         *
*                              CMPS 101: PA1                              *
*                                                                         *
*                             October 10, 2017                            *
*                                                                         *
*  _____________________________________________________________________  *
*                                                                         *
*                                List.java                                *
*                                                                         *
**************************************************************************/

// package thisoneguy;

public class List
{
    private class Node
    {
        public Node prev, next;
        int value;

        public Node(int value, Node prev, Node next) {
            this.value = value;
            this.prev = prev;
            this.next = next;
        }

        public Node(int value) {
      /*
      this.value = value;
      this.prev = null;
      this.next = null;
      */
            this(value, null, null);
        }
    }

    private Node head, tail, cursor;
    private int length, index;

  // Constructor
  public List () 
  {
    clear();
  }

  
  
/* ************************************************************************
*                                                                         *
*                            Access functions                             *
*                                                                         *
**************************************************************************/

  // Returns the number of elements in this list.  
  public int length()
  {
    return length;
  }
  
  // Returns front element. Pre: length() > 0.
  public int front() 
  {
    if (length < 0)
    {
      throw new IllegalStateException("ERROR: front() is being" + 
        " called on an empty List");
    }
    else 
    {
      return head.value;
    }
  }

  // Returns back element. Pre: length()>0.
  public int back() 
  {
    if (length < 0)
    {
      throw new IllegalStateException("ERROR: back() is being" + 
        " called on an empty List");
    }
    return tail.value; 
  }
  
  // Returns cursor element. Pre: length()>0, index()>=0.
  public int get() 
  {
    if (length < 0) 
    {
      throw new IllegalStateException("ERROR: get() is being" + 
        " called on an empty List");
    } 
    if (index < 0)
    {
      throw new IllegalStateException("ERROR: get() is called" +
        " with an undefined index on List");
    }
    else
    return cursor.value;
  }

  // If cursor is defined, returns the index of the cursor element, 
  // otherwise returns -1.
  public int index() 
  {
    if (cursor == null)
    {
        index = -1;
    }
      return index;
  }

  
  // Returns true if and only if this List and L are the same
  // integer sequence. The states of the cursors in the two Lists
  // are not used in determining equality
  boolean equals(List L) 
  {
    if (L == null)
      return false;
    
    return toString().equals(L.toString());
  }
    /*
    if(L == null || L.length() != length()) {
        return false;
    }
    Node i1 = head, i2 = L.head;
    while(i1 != null){
      if(i1.value != i2.value) {
        return false; 
      }
      i1 = i1.next;
      i2 = i2.next; 
    }  
    return true;
    */
/* ************************************************************************
*                                                                         *
*                         Manipulation procedures                         *
*                                                                         *
**************************************************************************/

// Resets this List to its original empty state.   
public void clear() 
{
  head = null;
  tail = null;
  cursor = null;
  length = 0;
  index = -1;
}

// If List is non-empty, places the cursor under the front element,
// otherwise does nothing.
public void moveFront() {
  if(length != 0) {
    cursor = head;
    index = 0;
  }
}  

// If List is non-empty, places the cursor under the back element,
// otherwise does nothing.
public void moveBack() {
  if(length != 0) {
    cursor = tail;
    index = length() - 1;
  }
}

// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
public void movePrev() {
  if(cursor != null){
    if(cursor == head) {
      cursor = null;
    } 
    else {
      cursor = cursor.prev;
      index--;
    }
  }
}

void moveNext() {
  if(cursor != null) {
    if(cursor == tail) {
      cursor = null;
    } 
    else {
      cursor = cursor.next;
      index++;
    }
  }
}

// Insert new element into this List. If List is non-empty,
// insertion takes place before front element.  
void prepend(int data) {
  Node node = new Node(data);

  if(length() == 0) {
      head = node;
      tail = node;
  }
  else {
      head.prev = node;
      node.next = head;
      head = node;
  }
    index++;
    length++;
}

// Insert new element into this List. If List is non-empty,
// insertion takes place after back element.
void append(int data)
{
  Node node = new Node(data);

  if(length() == 0)
  {
      head = node;
      tail = node;
  }
  else
  {
      tail.next = node;
      node.prev = tail;
      tail = node;
  }
    length++;
}


// Insert new element before cursor.
// Pre: length()>0, index()>=0.
void insertBefore(int data) {
  if(length <= 0 || index < 0) {
    throw new IllegalStateException("ERROR: List should not be empty");
  }
  
  if(index == 0) {
    prepend(data);
    return;
  }
  
  Node node = new Node(data, cursor.prev, cursor);
  cursor.prev = node;
  cursor = node.next;
  index++;
}
     
// Inserts new element after cursor.
// Pre: length()>0, index()>=0.
void insertAfter(int data) {
  if(length <= 0 || index < 0 ) {
   throw new IllegalStateException("ERROR: List should be non empty"); 
  }
  if(index == length() - 1) {
   append(data);
   return;
  }
  
  Node node = new Node(data, cursor.next, cursor);
  cursor.next = node;
  node.next.prev = node;
}
     
// Deletes the front element. Pre: length()>0.
void deleteFront() {
  if( length <= 0) {
    throw new IllegalStateException("ERROR: deleteFront() is " +
      "called on a empty list");
  }
  if(length > 1) {
    if(cursor == head) {
      head = null;
      index = -1;
    }
    head = head.next;
    length--;
  }
}

// Deletes the back element. Pre: length()>0.
void deleteBack() {
  if( length <= 0) {
    throw new IllegalStateException("deleteBack() is called on a " +
      "empty list");
  }
  if(length > 1) {
    if(cursor == head) {
      head = null;
      index = -1;
    }
    head = head.prev;
    length--;
  }
}

// Deletes cursor element, making cursor undefined.
// Pre: length()>0, index()>=0.
void delete() {
  if(length <= 0) {
    throw new IllegalStateException("List should be non-empty");
  }
  
  if (index < 0) {
  throw new IllegalStateException("Cursor should be defined");
  }
  if(cursor == head) {
    deleteFront(); 
  }
  else if(cursor == tail) {
    deleteBack();
  }
  else {
    cursor.prev.next = cursor.next;
    cursor.next.prev = cursor.prev;
    cursor = null;
    length--;
    index = -1;
  }
}

/* ************************************************************************
*                                                                         *
*                             Other Methords                              *
*                                                                         *
**************************************************************************/

// Overrides Object's to String method. Returns a String
// representation of this List consisting of a space
// separated sequence of integers, with front on left.
public String toString()
{
    Node node = head;
    String toString = new String();
    while(node != null)
    {
        toString = toString + String.valueOf(node.value) + " ";
        node = node.next;
    }
    return toString;
}

// Returns a new List representing the same integer sequence as this
// List. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copy() {
  List copy = new List(); 
    Node i = head;
    while (i != null){
      copy.append(i.value);
      i = i.next;
    }
  return copy;
}
}
