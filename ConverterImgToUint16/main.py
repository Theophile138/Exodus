import numpy as np
from PIL import Image
import tkinter as tk
from tkinter import filedialog, messagebox
import os


def rgb_to_rgb565(r, g, b):
    """Convert RGB to RGB565 format."""
    r = (r >> 3) & 0x1F  # 5 bits for red
    g = (g >> 2) & 0x3F  # 6 bits for green
    b = (b >> 3) & 0x1F  # 5 bits for blue
    return (r << 11) | (g << 5) | b


def image_to_rgb565_array(image_path):
    """Convert an image to a RGB565 array without resizing."""
    img = Image.open(image_path).convert('RGB')
    width, height = img.size
    rgb565_array = np.zeros((height, width), dtype=np.uint16)

    for y in range(height):
        for x in range(width):
            r, g, b = img.getpixel((x, y))
            rgb565_array[y, x] = rgb_to_rgb565(r, g, b)

    return rgb565_array, width, height


def save_arrays_to_header_file(images_dict, filename):
    """Save multiple RGB565 arrays to a single .h file."""
    with open(filename, 'w') as f:
        f.write("#ifndef IMAGE_DATA_H\n")
        f.write("#define IMAGE_DATA_H\n\n")

        for name, (array, width, height) in images_dict.items():
            f.write(f"const int image_{name}_width = {width};\n")
            f.write(f"const int image_{name}_height = {height};\n")
            f.write(f"const uint16_t image_{name}[] = {{\n")
            for row in array:
                f.write(", ".join(f"0x{value:04X}" for value in row) + ",\n")
            f.write("};\n\n")

        f.write("#endif // IMAGE_DATA_H\n")


def select_folder():
    """Open a file dialog to select a folder and process all images inside."""
    folder_path = filedialog.askdirectory()
    if folder_path:
        try:
            images_dict = {}
            valid_extensions = {".png", ".jpg", ".jpeg", ".bmp"}

            for file_name in os.listdir(folder_path):
                file_path = os.path.join(folder_path, file_name)
                if os.path.isfile(file_path) and os.path.splitext(file_name)[1].lower() in valid_extensions:
                    name = os.path.splitext(file_name)[0]  # Extract filename without extension
                    rgb565_array, img_width, img_height = image_to_rgb565_array(file_path)
                    images_dict[name] = (rgb565_array, img_width, img_height)

            if images_dict:
                save_path = filedialog.asksaveasfilename(defaultextension=".h", filetypes=[("Header files", "*.h")])
                if save_path:
                    save_arrays_to_header_file(images_dict, save_path)
                    messagebox.showinfo("Success", "Images converted and saved successfully!")
            else:
                messagebox.showwarning("No Images Found", "No valid images found in the selected folder.")
        except Exception as e:
            messagebox.showerror("Error", str(e))


# Create a simple GUI
root = tk.Tk()
root.title("Image to RGB565 Converter")
root.geometry("400x200")

# Select Folder Button
button = tk.Button(root, text="Select Folder", command=select_folder)
button.pack(pady=20)

root.mainloop()
