# CS585-Shaokang-Wang

1. Everything must be in well-formed English where appropriate.

2. The first line of every file must contain a C++ style comment with the file name (// file_name.h)

3. A space must be after the comment double character for all comments (// this is a comment)

4. All non-trivial length comments must end in a period.

5. The private section must come before the public section in a header.

6. Elements interior to a namespace are not tabbed in.

7. The private and public keywords must be indented 2 space characters.

8. Elements interior should be appropriately tabbed (with spaces, not tab characters)

9. Classes are upper camel case (DynamicArray)

10.Functions are lower camel case (addElement)

11.Reusable constants (meaning they are outside the scope of a function) must use upper snake case (DEGREES_IN_RADIANS)

12.Boolean variables must contain an appropriate form at the beginning of the variable name (isAvailable, wasCreated, shouldExecute, canAttack, etc.)

13.Generally, primitive type specifics should never be used in a variable name (NO: nameStr, nameString, strName, etc., note that things like weaponCount is acceptable, it is not the type, it is a clearer meaning)

14.No definition (implementation) within body of class declaration (interface)

15.Header may only contain definitions of inline functions and free functions (for non-template classes)

16.Header MUST contain include guards in the form of INCLUDED_CLASS_NAME (#pragma once can be used, but is not a replacement for proper include guards)

17.All helper functions, internal structs, etc. not meant to be visible or used by external developers MUST use anonymous namespaces unless a private struct makes more sense

18.No use of the protected keyword

19.There must be spaces interior to parenthesis ( attack( int targetId ); )

20.Curly braces must be vertically aligned

21.All functions should contain appropriate early-out clauses at the top most portion of the function (for example, immediately erroring at the top if variables are null and it is required that they are not null)

22.0 or nullptr must be used instead of NULL

23.No magic numbers

24.No direct heap allocations unless absolutely necessary

25.Allocations must be wrapped within an appropriate container class for life cycle management

26.Only pass pointers if the value is mutable

27.Primitives should be passed by copy (const is not necessary)

28.Non-primitives meant to not be mutated must be passed by const reference

29.All non-trivial classes must implement orthodox canonical form or appropriately control the copy constructor

30.Headers must contain comments detailing every function’s use and expected behavior (as well as undefined behavior), comments should be BELOW the function’s declaration, spaced two characters beyond the function’s tabbing

31.No code is allowed to break the 80 character line limit, code must be intelligently broken up to read easily, subsequent code from a broken line should be tabbed one full tab (usually 4 spaces)

32.All comments must be in C++ style comments (NOT C); this includes multi line comments

33.Anything non-obvious code should have appropriate comments (not over commented, not under commented)

34.Every class must implement an OStream insertion operator (<<) that writes a valid json string, this must be implemented as a free operator, not a friend

35.All public utility functions (for example, builders and converters) must be implemented as static functions interior to a struct

36.No cyclical dependencies are allowed (if you find yourself writing a forward declaration, you are doing it wrong)

37.No unused includes can be present in the header (if the header does not use the include, the include must be in the cpp)

38.The first include in every cpp MUST be the header for the cpp

39.Includes must be alphabetical

40.Private data members in a header must be prefixed with d_ (d for data)

41.The inline keyword must be on its own line

42.Sections of a header (for example, the constructor section) must be annotated with a C++ style comment line detailing the section in all caps (// CONSTRUCTORS, // ACCESSORS, // MUTATORS, // FREE OPERATORS, // MEMBER FUNCTIONS), the corresponding sections must be in header inline implementations and cpp’s, all functions must be implemented in the same order they are declared

43.All functions that do not modify internal state must be marked with a post-fix const

44.Accessor functions must be named the same as the interior data member they retrieve without the prefixed d_ (if you have float d_time, you would then have a float time() const function for retrieving the value)

45.Mutators must be prefixed with set (for the same example, you would have a void setTime( float time ))

46.All namespaces must have a comment on the closing bracket indicating what namespace was closed in the form of // End nspc namespace (where nspc is the namespace being closed)

47.All conditional blocks (if, for, while, etc.) must use curly braces


