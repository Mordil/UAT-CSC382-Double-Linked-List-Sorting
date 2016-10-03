#pragma once

template<typename K, typename V>
class MyNode
{
public:
	MyNode(const K key, const V data) : _key(key), _data(data), _previousNode(NULL), _nextNode(NULL) { }

	MyNode(const K key, const V data, MyNode& previous)
		: MyNode(key, data) { _previousNode = &previous; }

	MyNode(const K key, const V data, MyNode& previous, MyNode& next)
		: MyNode(key, data, previous) { _nextNode = &next; }
	
	void SetPrevious(MyNode* newPrevious) { _previousNode = newPrevious; }
	void SetNext(MyNode* newNext) { _nextNode = newNext; }

	void SetData(const V& newData) { _data = newData; }

	const K& GetKey() { return _key; }
	const V& GetData() { return _data; }

	MyNode*& GetNext() { return _nextNode; }
	MyNode*& GetPrevious() { return _previousNode; }

private:
	K _key;
	V _data;

	MyNode* _previousNode;
	MyNode* _nextNode;
};
