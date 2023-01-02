#include <typeinfo>
#include <iostream>

class object {
	private:
		/** 
		 * TODO: Using the idea of dynamic binding, and generalization to complete the definition of struct `object_pointer` and `T_pointer` below.
		 * You are ONLY allowed to modify the struct `object_pointer` and `T_pointer`.
		 * You are NOT allowed to add data member to both structs.
		*/
		
		// Your modification starts here.
		struct object_pointer {
			virtual const std::type_info& type() const = 0;
			virtual object_pointer* copy() const = 0;
			virtual ~object_pointer() = default;
			
			virtual object add(const object_pointer* other) const = 0;
			virtual bool equals(const object_pointer* other) const = 0;
			virtual void stream(std::ostream &os) const = 0;
		};
		// Your modification ends here.

		// Your modification starts here.
		template <typename T>
		struct T_pointer: object_pointer {
			T value;
			T_pointer(T value);
			const std::type_info& type() const override;
			object_pointer* copy() const override;
			~T_pointer() = default;
			
			object add(const object_pointer* other) const override;
			bool equals(const object_pointer* other) const override;
			void stream(std::ostream &os) const override;
		};
		// Your modification ends here.
		
		object_pointer* obj_ptr;

	public:

		template <typename T>
		object(const T& value);

		object(const object& other);

		~object();

		object& operator=(const object& other);

		const std::type_info& type() const;

		template <typename T>
		T cast_back() const;

		//Default constructor defaults a value of int 0
		object() : object(0) {}

		/**
		 * Bonus part of the assignment. You may choose to or not to finish it.
		 * You will need to uncomment the respective function declaration if you have implemented it.
		*/

		object operator+(const object& other) const;
		bool operator==(const object& other) const;
		friend std::ostream& operator<<(std::ostream &os, const object& obj);
};

#include "object.tpp"
