# Electra-Lang
Small esolang inspired by AsciiDots. Uses instruction pointers that acts like currents in electricity.

## How Electra works?

Electra has generators and components. Generators generate currents and components interperate currents that came through them. Electra uses a single stack for memory management.

### **Currents**
Currents are instruction pointers in electra. They call work() function of the component that they are on. A component's work() function returns a boolean value. If it is false current gets killed.

### **Generators (<, >, ^, v)**
Generators generate currents at the beginning of the program and become unused after that. They generate current based on their ascii character (> generates a current to the right, < generates a current to the left etc.)

### **Components**
Components are the elements that gives electra its functionality. Each component has its own job and can generate or remove existing currents.

**TODO:** Add explanation for each component and portals.

**TODO:** Add example codes for truth-machine, FizzBuzz, Hello World!
