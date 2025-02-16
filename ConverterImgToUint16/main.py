import numpy as np
from PIL import Image
import tkinter as tk
from tkinter import filedialog, messagebox


def rgb_to_rgb565(r, g, b):
    """Convert RGB to RGB565 format."""
    r = (r >> 3) & 0x1F  # 5 bits for red
    g = (g >> 2) & 0x3F  # 6 bits for green
    b = (b >> 3) & 0x1F  # 5 bits for blue
    return (r << 11) | (g << 5) | b


def image_to_rgb565_array(image_path, size):
    """Convert an image to a RGB565 array."""
    img = Image.open(image_path).convert('RGB')
    img = img.resize(size, Image.LANCZOS)  # Resize the image using LANCZOS filter
    width, height = img.size
    rgb565_array = np.zeros((height, width), dtype=np.uint16)

    for y in range(height):
        for x in range(width):
            r, g, b = img.getpixel((x, y))
            rgb565_array[y, x] = rgb_to_rgb565(r, g, b)

    return rgb565_array


def save_array_to_header_file(array, filename):
    """Save the RGB565 array to a .h file."""
    with open(filename, 'w') as f:
        f.write("#ifndef IMAGE_DATA_H\n")
        f.write("#define IMAGE_DATA_H\n\n")
        f.write("const uint16_t image_data[] = {\n")

        for row in array:
            f.write(", ".join(f"0x{value:04X}" for value in row) + ",\n")

        f.write("};\n\n")
        f.write("#endif // IMAGE_DATA_H\n")


def select_image():
    """Open a file dialog to select an image."""
    file_path = filedialog.askopenfilename(filetypes=[("Image files", "*.png;*.jpg;*.jpeg;*.bmp")])
    if file_path:
        try:
            width = int(width_entry.get())
            height = int(height_entry.get())
            rgb565_array = image_to_rgb565_array(file_path, (width, height))
            save_path = filedialog.asksaveasfilename(defaultextension=".h", filetypes=[("Header files", "*.h")])
            if save_path:
                save_array_to_header_file(rgb565_array, save_path)
                messagebox.showinfo("Success", "Image converted and saved successfully!")
        except ValueError:
            messagebox.showerror("Error", "Please enter valid integer values for width and height.")
        except Exception as e:
            messagebox.showerror("Error", str(e))


# Create a simple GUI
root = tk.Tk()
root.title("Image to RGB565 Converter")
root.geometry("400x200")

# Width and Height Entry
tk.Label(root, text="Width:").pack(pady=5)
width_entry = tk.Entry(root)
width_entry.pack(pady=5)

tk.Label(root, text="Height:").pack(pady=5)
height_entry = tk.Entry(root)
height_entry.pack(pady=5)

# Select Image Button
button = tk.Button(root, text="Select Image", command=select_image)
button.pack(pady=20)

root.mainloop()