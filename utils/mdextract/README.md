# mdextract

A tool to extract markdown from comments starting with a tilde. This
format is used in the examples code to document it.

## Example

For the input file:

```c++
    //~ # Simple example
    //~
    //~ First of all, we include the needed header:
    
    #include <iostream>
    
    //~ then we create our `main` function:
    
    int main()
    {
        //~ and write a message:
        
        std::cout << "Message!" << std::endl;
    }
    
    //~ That's it!
```

the following markdown is generated:

```markdown
    # Simple example
    
    First of all, we include the needed header:
    
    ```c++
    #include <iostream>
    ```
    
    then we create our `main` function:
    
    ```c++
    int main()
    {
    ```
    
    and write a message:
    
    ```c++
        std::cout << "Message!" << std::endl;
    }
    ```
    
    That's it!
```