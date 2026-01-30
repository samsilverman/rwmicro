# rwmicro — Applications

This directory contains command-line tools built on top of the `rwmicro` library and demonstrate typical workflows.

> [!NOTE]
> Each application includes a detailed description, usage examples, and parameter explanations in the docstring at the top of its corresponding source file.

## Available Applications

| Application | Description |
| - | - |
| **`1_SingleDesign`** | ***Command-line tool for generating a single valid microstructure.*** This program generates a random-walk microstructure of size `nx`x`ny`. A target mass is drawn at random, and the generator attempts to produce a valid microstructure up to `retries` times. If all attempts fail, a new random mass is drawn and the process repeats until a valid sample is obtained. |
| **`2_BatchedDesigns`** | ***Command-line tool for generating a batch of valid microstructures.*** This program generates a batch of `numSamples` random-walk microstructures of size `nx`x`ny`. For each sample, a target mass is drawn at random, and the generator attempts to produce a valid microstructure up to `retries` times. If all attempts fail, a new random mass is drawn and the process repeats until a valid sample is obtained. |
