# C linked list in Ruby w/FFI

require 'ffi'

module LinkedList
	extend FFI::Library
	ffi_lib './liblinkedlist.so'

	class Node < FFI::Struct
		layout :data, :int,
			   :next, :pointer
	end


  # Attach the functions from the shared library
  attach_function :create_node, [:int], :pointer
  attach_function :append, [:pointer, :int], :void
  attach_function :get_data, [:pointer], :int
  attach_function :print_list, [:pointer], :void
  attach_function :free_list, [:pointer], :void
end

# Create the linked list and manipulate it
head = FFI::MemoryPointer.new(:pointer)

# Append some values
LinkedList.append(head, 10)
LinkedList.append(head, 20)
LinkedList.append(head, 30)

# Print the list
LinkedList.print_list(head.get_pointer(0))

# Get data from the first node
first_node = head.get_pointer(0)
puts "Data in the first node: #{LinkedList.get_data(first_node)}"

# Free the list
LinkedList.free_list(head.get_pointer(0))