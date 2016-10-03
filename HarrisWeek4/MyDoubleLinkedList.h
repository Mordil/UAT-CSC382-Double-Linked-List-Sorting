#pragma once

#include <vector>
#include <string>

#include "MyNode.h"

template<typename K, typename V>
class MyDoubleLinkedList
{
	typedef MyNode<K, V> Node;

public:
	/* Initializes an empty list. */
	MyDoubleLinkedList() : _rootNode(NULL) { }
	~MyDoubleLinkedList() { }

	/* Inserts a new node in the list with the provided key and value. */
	void Insert(const K& key, const V& value)
	{
		// otherwise search for the node
		Node* nodeToUpdate = FindNode(key);

		// if the node doesn't exist, add it
		if (nodeToUpdate == NULL)
		{
			_addNode(key, value);
		}
		else
		{
			// otherwise, update it
			nodeToUpdate->SetData(value);
		}
	}

	void SortedInsert(const K& key, const V& value)
	{
		// if the root is null, just assign the new node
		if (_rootNode == NULL)
		{
			_rootNode = new Node(key, value);
			_nodeCount++;
		}
		// if there is only 1 element in the list
		else if (_rootNode->GetNext() == NULL)
		{
			// create the node
			Node* newNode = new Node(key, value);

			// if the new node's value is less than the root
			if (newNode->GetData() < _rootNode->GetData())
			{
				// grab a reference to the pointer to the old root
				Node* oldRoot = _rootNode;
				// assign the new node as the new root
				_rootNode = newNode;

				// link the new root to the old root
				_rootNode->SetNext(oldRoot);
				_rootNode->SetPrevious(oldRoot);

				// link the old root to the new root
				oldRoot->SetPrevious(_rootNode);
				oldRoot->SetNext(_rootNode);
			}
			else
			{
				// otherwise, just append it to the right as normal
				_rootNode->SetNext(newNode);
				_rootNode->SetPrevious(newNode);
				newNode->SetPrevious(newNode);
				newNode->SetNext(_rootNode);
			}

			_nodeCount++;
		}
		else
		{
			// create a new node and grab a pointer to the next node
			Node* newNode = new Node(key, value);
			Node* currentNode = _rootNode;

			if (currentNode->GetData() > newNode->GetData())
			{
				// grab the old previous for root
				Node* oldPrevious = _rootNode->GetPrevious();
				// maintain a reference to the old root
				Node* oldRoot = _rootNode;
				// set the new node's previous & next links
				newNode->SetPrevious(oldPrevious);
				newNode->SetNext(oldRoot);
				// assign the new node as the root
				_rootNode = newNode;
				
				// link the new root as the old root's previous
				oldRoot->SetPrevious(_rootNode);
				// link the new root to the previous to the old root
				oldPrevious->SetNext(_rootNode);
				_nodeCount++;
				return;
			}
			else
			{
				// start the rest of the logic off of the second element
				currentNode = _rootNode->GetNext();
			}

			// while the node is not null,
			// the node's value is less than the new node
			// and the node is not at the end of the list
			while (currentNode != NULL &&
				   currentNode->GetData() < newNode->GetData() &&
				   currentNode->GetNext() != _rootNode)
			{
				currentNode = currentNode->GetNext();
			}

			Node* smallerNode = currentNode->GetPrevious();

			newNode->SetNext(currentNode);
			newNode->SetPrevious(smallerNode);

			smallerNode->SetNext(newNode);
			currentNode->SetPrevious(newNode);
			
			_nodeCount++;
		}
	}
	
	/*
		I wouldn't structure the methods the way that they are, but given that the assignment calls out this specific signature, I have implemented the Delete
		method by accepting a pointer address and comparing addresses.
		If I was writing this for production, I would accept a key, or a value, or both to compare to see if it's the node, as there's too many scenarios to handle from being passed a pointer.
	*/

	/* Deletes the node if it exists in the array. */
	void Delete(Node*& nodeToDelete)
	{
		// Find the node matching the passed node's key
		Node* node = FindNode(nodeToDelete->GetKey());
		
		// if the node exists in the list
		if (nodeToDelete == node)
		{
			// grab its previous & next nodes
			Node* nextNode = node->GetNext();
			Node* previousNode = node->GetPrevious();

			if (node == _rootNode)
			{
				if (node == nextNode && node == previousNode)
				{
					_rootNode = NULL;
					_nodeCount--;
					return;
				}
				else
				{
					_rootNode = nextNode;
				}
			}

			// link the two together
			nextNode->SetPrevious(previousNode);
			previousNode->SetNext(nextNode);

			// delete the data in this list and decrement the counter
			delete node;
			_nodeCount--;
		}
	}
		
	/* Prints the current size of the list to the console. */
	void PrintCount() { std::cout << "The current size: " << to_string(_nodeCount) << "\n"; }

	/* Iterates through the list and prints the address of each item in the list, as well as the addresses of their next/previous nodes. */
	void PrintContents()
	{
		std::cout << "Contents (starting from root):\n";

		Node* node = _rootNode;
		while (node != NULL)
		{
			std::cout << "Node with value: " << node->GetData() << "\n";

			if (node->GetNext() == _rootNode)
			{
				node = NULL;
			}
			else
			{
				node = node->GetNext();
			}
		}

		std::cout << "\n\n";
	}
	
	/* Returns a pointer to a Node if one exists with the provided key, or a pointer to NULL otherwise. */
	Node* FindNode(const K& key) { return _findNode(key, _rootNode); }

	/*
		I know the extra credit specified the max/min KEYS, but I thought it made more sense to compare VALUES.
	*/

	/* Returns a pointer to a Node with the maximum value in the list, or a pointer to NULL otherwise. */
	Node* GetMaximum() { return _compareNodeValues(true); }

	/* Returns a pointer to a Node with the minimum value in the list, or a pointer to NULL otherwise. */
	Node* GetMinimum() { return _compareNodeValues(false); }

	/* Returns a new linked list sorted from smallest to largest using InsertSort. */
	MyDoubleLinkedList Sorted()
	{
		MyDoubleLinkedList newList;
		Node* node = _rootNode;

		while (node != NULL && node->GetNext() != _rootNode)
		{
			newList.SortedInsert(node->GetKey(), node->GetData());
			node = node->GetNext();
		}

		return newList;
	}

	/* Returns a new linked list sorted from smallest to largest using SelectionSort. */
	MyDoubleLinkedList SelectionSorted()
	{
		MyDoubleLinkedList copyOfSelf(*this);
		MyDoubleLinkedList returnList;
		Node* minimum = copyOfSelf.GetMinimum();

		while (minimum != NULL)
		{
			returnList.Insert(minimum->GetKey(), minimum->GetData());
			copyOfSelf.Delete(minimum);
			minimum = copyOfSelf.GetMinimum();
		}

		return returnList;
	}

private:
	int _nodeCount = 0;

	Node* _rootNode;

	void _addNode(const K& key, const V& value)
	{
		if (_rootNode == NULL)
		{
			_rootNode = new Node(key, value);
			_nodeCount++;
			return;
		}

		Node* previousNode = _rootNode;
		Node* endNode = _rootNode->GetNext();

		if (endNode == NULL)
		{
			Node* newNode = new Node(key, value);
			newNode->SetPrevious(previousNode);
			newNode->SetNext(previousNode);

			previousNode->SetPrevious(newNode);
			previousNode->SetNext(newNode);
			_nodeCount++;
			return;
		}
		else
		{
			while (endNode->GetNext() != _rootNode)
			{
				previousNode = endNode;
				endNode = endNode->GetNext();
			}

			// create the node and attach it to the old end node
			endNode->SetNext(new Node(key, value));
			// grab a pointer address to the new node
			Node* newNode = endNode->GetNext();

			// set the new node's previous and next
			newNode->SetPrevious(endNode);
			newNode->SetNext(_rootNode);

			_rootNode->SetPrevious(newNode);

			_nodeCount++;
		}
	}

	Node* _findNode(const K& key, Node*& startingNode)
	{
		if (startingNode == NULL)
		{
			return startingNode;
		}
		else if (startingNode->GetKey() != key)
		{
			Node* nextNode = startingNode->GetNext();

			if (nextNode == _rootNode)
			{
				return NULL;
			}

			return _findNode(key, nextNode);
		}
		else
		{
			return startingNode;
		}
	}

	Node* _compareNodeValues(bool greaterThanComparison)
	{
		Node* node = _rootNode;
		Node* maxValueNode = (_rootNode == NULL) ? NULL : _rootNode;

		while (node != NULL)
		{
			if (greaterThanComparison)
			{
				if (node->GetData() > maxValueNode->GetData())
				{
					maxValueNode = node;
				}
			}
			else
			{
				if (node->GetData() < maxValueNode->GetData())
				{
					maxValueNode = node;
				}
			}

			Node* nextNode = node->GetNext();

			if (nextNode == _rootNode)
			{
				node = NULL;
			}
			else
			{
				node = nextNode;
			}
		}

		return maxValueNode;
	}
};
