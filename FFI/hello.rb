
# load C shared library function with FFI 

require 'ffi'

module Hello
	extend FFI::Library
	ffi_lib './libhello.so'

	attach_function :hello_world, [], :string
end

puts Hello.hello_world
