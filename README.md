# UEIconGenerator

**UEIconGenerator** is a custom Icon Generator for Unreal Engine that creates its own `UWorld` using `SAssetEditorViewport`.  

### Features
- Generates custom icons for various asset types.
- Integrates with Unreal Engine's asset workflow.
- Uses `UWorld` to render and manage icon generation independently.

### Current Status
This project is a **Work in Progress**. Contributions and feedback are welcome.

---

## How It Works
1. **UWorld Creation**:  
   The generator creates a separate `UWorld` instance for rendering icons.

2. **Editor Viewport Integration**:  
   Leverages `SAssetEditorViewport` for visualizing and editing the generated icons.

3. **Supported Assets**:  
   Currently supports generating icons for:
   - Static Meshes
   - Skeletal Meshes
   - Blueprints  

   *(More asset types may be supported in future updates.)*

---

## Getting Started

### Prerequisites
- Unreal Engine 5.x
- Basic understanding of Unreal's Editor Utility Widgets (optional but helpful).

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/your-repo/UEIconGenerator.git
   ```
2. Add the project to your Unreal Engine plugins folder.

3. Enable the plugin in Unreal Engine's Plugin Manager.

---

## Usage
1. Open the **UEIconGenerator** tool from the Unreal Editor.
2. Select the asset(s) you want to generate icons for.
3. Customize settings (if available).
4. Click **Generate Icon** to create custom icons for your assets.

---

## License
This project is licensed under the [MIT License](LICENSE).  

---

### Preview

![Icon Generator Preview](https://github.com/user-attachments/assets/20bd33bd-20d5-44bb-a117-368f790317c0)

---

### Contributing
Contributions are welcome!  
Please fork the repository, make changes, and submit a pull request.

---

### Contact
For questions or suggestions, feel free to open an issue in the repository.  
