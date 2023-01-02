template <typename K, typename V>
struct Node {
	K key;
	V value;
	Node** nexts;
	int levels;
};

template <typename K, typename V>
class Skiplist {
	Node* head;
	double prob;
};

class object {
	object_pointer* obj_ptr;
};

struct object_pointer {
	virtual const std::type_info& type() const = 0;
	virtual object_pointer* copy() const = 0;
	virtual ~object_pointer() = default;
	
	virtual object_pointer* add(const object_pointer* other) const = 0;
	virtual bool equals(const object_pointer* other) const = 0;
	virtual void stream(std::ostream &os) = 0;
};

template <typename T>
struct T_pointer {
	T value;
	T_pointer(T value);
	const std::type_info& type() const override;
	object_pointer* copy() const override;
	~T_pointer() = default;
	
	object_pointer* add(const object_pointer* other) const override;
	bool equals(const object_pointer* other) const override;
	void stream(std::ostream &os) override;
};