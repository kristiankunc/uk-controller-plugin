# UK Controller Plugin - Copilot Instructions

## Project Overview

The VATSIM UK Controller Plugin is a C++ plugin for EuroScope 3.2 that provides functionality to controllers of UK positions on the VATSIM network. The plugin works in cooperation with a Plugin API to offer useful features for air traffic control operations.

**Key Features:**
- Real-time flight data processing
- Controller coordination tools
- Event-driven architecture
- Asynchronous operations for external API calls
- Extensive testing coverage

## Architecture

**Main Components:**
- **Core Plugin** (`src/plugin/`) - Main plugin logic and EuroScope integration
- **Loader** (`src/loader/`) - Plugin loader and initialization
- **Updater** (`src/updater/`) - Handles plugin updates  
- **Utils** (`src/utils/`) - Shared utilities and common functionality

**Output Products:**
- `UKControllerPluginCore.dll` - Main plugin binary
- `UKControllerPlugin.dll` - Loader binary  
- `UKControllerPluginUpdater.dll` - Updater binary

## Development Environment

### Prerequisites
- Windows (development primarily targets Windows)
- Visual Studio 2019+ or Visual Studio Code with C++ extensions
- CMake 3.15+
- Ninja build system
- clang-cl compiler (part of LLVM/Clang)
- Git with submodules support

### Build System
- **Build Tool**: CMake with Ninja generator
- **Compiler**: clang-cl (Clang with MSVC compatibility)
- **Architecture**: 32-bit (Win32) - this is a hard requirement
- **Configurations**: Debug (with symbols) and Release (optimized)

### Dependencies
- **cURL** - HTTP client library (statically linked)
- **Google Test/Mock** - Testing framework
- **nlohmann/json** - JSON parsing
- **spdlog** - Logging library
- **EuroScope SDK** - EuroScope plugin development
- Various third-party libraries in `third_party/`

## Building the Project

### Standard Build (Local Development)
```bash
# Configure the build
cmake -DCMAKE_BUILD_TYPE=Release -G Ninja -B build

# Build the project
ninja -C build

# Or build specific targets
ninja -C build UKControllerPluginCore
```

### Development with Visual Studio
1. Open the project folder in Visual Studio
2. CMake will automatically configure
3. Select the desired configuration (Debug/Release)
4. Build using Visual Studio's build system

### Container Build (Recommended for Consistency)
The project includes Docker support for reproducible builds:

```bash
# Using Docker directly
docker run -it ./dockerfile

# Using VS Code Dev Containers
# Open in VS Code and use "Dev Containers: Reopen in Container"
```

See `docs/CONTAINER_BUILD.md` for detailed container build instructions.

## Testing

### Test Framework
- **Framework**: Google Test and Google Mock
- **Runner**: ctest (CMake's testing tool)
- **Test Projects**: 
  - `test/loader/` - Loader component tests
  - `test/plugin/` - Core plugin tests  
  - `test/updater/` - Updater component tests
  - `test/utils/` - Utility function tests

### Running Tests
```bash
# Run all tests
cd build
ctest -C Release --output-on-failure

# Run specific test suite
ctest -C Release -R "UtilsTest"

# Run tests with verbose output
ctest -C Release --output-on-failure --verbose
```

### Test Organization
- Tests are co-located with source code in parallel `test/` directories
- Each test file typically tests one source file or component
- Use descriptive test names: `TEST_F(ClassNameTest, ItDoesSpecificThing)`
- Prefer real objects over mocks when possible
- **Coverage Requirement**: All code must be covered by automated tests

## Code Style and Quality

### Formatting
- **Tool**: clang-format (configuration in `.clang-format`)
- **Enforcement**: Automatic checking in CI/CD
- **Usage**: Configure your editor to run clang-format on save

```bash
# Format specific files
clang-format -i src/plugin/MyFile.cpp

# Check formatting (dry run)
clang-format --dry-run --Werror src/plugin/MyFile.cpp
```

### Static Analysis
- **Tool**: clang-tidy (configuration in `.clang-tidy`)
- **Usage**: Run on changed files during development

```bash
# Run clang-tidy on specific files
clang-tidy src/plugin/MyFile.cpp -p build
```

### Code Standards
- **C++ Standard**: C++20
- **Style**: Follow existing conventions in the codebase
- **Interface Design**: Use interfaces around external dependencies
- **Async Operations**: Use async patterns for long-running operations
- **Error Handling**: Proper exception handling and error propagation

## File Organization

```
uk-controller-plugin/
├── src/                    # Source code
│   ├── plugin/            # Main plugin implementation
│   ├── loader/            # Plugin loader
│   ├── updater/           # Update mechanism
│   └── utils/             # Shared utilities
├── test/                  # Test code (mirrors src structure)
├── docs/                  # Documentation
├── third_party/           # External dependencies
├── resource/              # Windows resources
├── CMakeLists.txt         # Root CMake configuration
└── .github/               # GitHub Actions workflows
```

### Key Files
- `CMakeLists.txt` - Root build configuration
- `src/*/CMakeLists.txt` - Component build configurations  
- `.github/workflows/build.yml` - CI/CD pipeline
- `package.json` - Semantic release configuration
- `docs/README.md` - Main project documentation

## Common Development Tasks

### Adding New Features
1. **Plan**: Discuss features in issues before implementation
2. **Create**: Add source files in appropriate `src/` subdirectory
3. **Test**: Create corresponding test files in `test/` subdirectory
4. **Build**: Update relevant `CMakeLists.txt` if adding new files
5. **Verify**: Ensure tests pass and code formats correctly

### Making Changes
1. **Branch**: Create feature branch from `main`
2. **Develop**: Make atomic commits with clear messages
3. **Test**: Ensure all tests pass locally
4. **Format**: Run clang-format on changed files
5. **PR**: Submit pull request with clear description

### Debugging
1. **Build**: Use Debug configuration for symbol information
2. **IDE**: Use Visual Studio or VS Code debugging features
3. **Logs**: Use spdlog for runtime debugging information
4. **Tests**: Write failing tests to reproduce issues

## CI/CD Pipeline

### GitHub Actions Workflow
The build pipeline (`.github/workflows/build.yml`) includes:

1. **Environment Setup**
   - Windows 2019 runner
   - Visual Studio shell configuration
   - cURL building and caching
   - Node.js/Yarn for semantic-release

2. **Build Process**
   - CMake configuration with Ninja
   - Ninja build execution
   - Binary artifact collection

3. **Quality Checks**
   - Test execution with ctest
   - clang-format verification
   - clang-tidy static analysis (currently disabled on Windows)

4. **Release** (on main/beta/alpha branches)
   - Semantic versioning
   - GitHub release creation
   - Binary artifact publishing

### Branch Strategy
- **main** - Stable releases
- **beta** - Beta releases with pre-release flag
- **alpha** - Alpha releases with pre-release flag
- Feature branches should target `main`

## Dependencies and External APIs

### Managing Dependencies
- **Third-party**: Most dependencies are included as git submodules in `third_party/`
- **cURL**: Built from source during CI, cached between runs
- **System Libraries**: Windows system libraries linked directly

### External Integrations
- **Plugin API**: RESTful API for data exchange
- **EuroScope**: Plugin host application
- **GitHub API**: For version checking and updates

## Performance Considerations

### Threading
- **Main Thread**: EuroScope runs on single thread - avoid blocking operations
- **Async Operations**: Long-running tasks (HTTP requests) use separate threads
- **Event Driven**: Architecture based on EuroScope event handlers

### Memory Management
- **RAII**: Use smart pointers and RAII patterns
- **DLL Boundaries**: Careful memory management across DLL boundaries
- **Optimization**: Release builds use aggressive compiler optimizations

## Troubleshooting

### Common Build Issues
- **Submodules**: Ensure all submodules are properly initialized
- **cURL**: Check cURL environment variables if HTTP requests fail
- **Architecture**: Verify 32-bit toolchain is being used
- **Line Endings**: Ensure proper line endings (especially in Docker)

### Testing Issues
- **Mock Setup**: Verify mock expectations are properly configured
- **Test Data**: Check test data setup and cleanup
- **Async Tests**: Handle timing issues in asynchronous test scenarios

### Debug Tips
- Use Debug configuration for development
- Enable verbose logging with spdlog
- Check EuroScope plugin logs for runtime issues
- Use Windows debugging tools for crash analysis

## Contributing

See `docs/CONTRIBUTING.md` for detailed contribution guidelines including:
- Code of conduct expectations
- Pull request requirements
- Commit message conventions
- Review process

Remember: All code changes must include comprehensive test coverage!