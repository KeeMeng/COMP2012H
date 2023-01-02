using namespace std;

template <typename T>
object::T_pointer<T>::T_pointer(T value_) {
	value = value_;
}

template <typename T>
const std::type_info& object::T_pointer<T>::type() const {
	return typeid(T);
}

template <typename T>
object::object_pointer* object::T_pointer<T>::copy() const {
	return new T_pointer<T>(value);
}


template <typename T>
object::object(const T& value) {
	obj_ptr = new T_pointer<T>(value);
}

object::~object() {
	if (obj_ptr != nullptr) {
		delete obj_ptr;
	}
}

object& object::operator=(const object& other) {
	if (this != &other) {
		if (obj_ptr != nullptr) {
			delete obj_ptr;
		}
		obj_ptr = other.obj_ptr->copy();
	}
	return *this;
}

object::object(const object& other) {
	obj_ptr = nullptr;
	*this = other;
}

const std::type_info& object::type() const {
	return obj_ptr->type();
}

template <typename T>
T object::cast_back() const {
	if (type() == typeid(T)) {
		return dynamic_cast<T_pointer<T>*>(obj_ptr)->value;
	} else {
		throw std::runtime_error("Object casting failed!");
	}
}


// bonus tasks
template <typename T>
object object::T_pointer<T>::add(const object_pointer* other) const {
	return object(this->value + dynamic_cast<const T_pointer<T>*>(other)->value);
}

object object::operator+(const object& other) const {
	if (this->type() == other.type()) {
		return this->obj_ptr->add(other.obj_ptr);
	} else {
		throw std::runtime_error("Types needed to be the same when performing +");
	}
}

template <typename T>
bool object::T_pointer<T>::equals(const object_pointer* other) const {
	return (this->value == dynamic_cast<const T_pointer<T>*>(other)->value);
}

bool object::operator==(const object& other) const {
	if (this->type() == other.type()) {
		return this->obj_ptr->equals(other.obj_ptr);
	} else {
		return false;
	}
}

template <typename T>
void object::T_pointer<T>::stream(std::ostream &os) const {
	os << value;
}

std::ostream& operator<<(std::ostream &os, const object& obj) {
	obj.obj_ptr->stream(os);
	return os;
}