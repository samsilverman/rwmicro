# rwmicro - Contributing

1. Go to [samsilverman/rwmicro](https://github.com/samsilverman/rwmicro) and fork the project.

2. Clone the fork to your local computer:

    ```bash
    git clone https://github.com/YourUsername/rwmicro.git
    ```

3. Create your feature branch:

    ```bash
    git checkout -b feature/NewFeature
    ```

4. Commit your changes:

    ```bash
    git commit -m "Add a new feature."
    ```

5. Push to the branch:

    ```bash
    git push origin feature/NewFeature
    ```

6. Open a pull request.

    Prior to opening a pull request, the contribution must *pass the unit tests*:

    ```bash
    mkdir build && cd build
    cmake -DRWMICRO_BUILD_TESTS=ON ..
    make -j8
    ./tests/rwmicro_tests
    ```

    Adding new code? Please also add new test cases covering your feature or bug fix.
