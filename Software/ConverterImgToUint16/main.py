import numpy as np
from PIL import Image
import tkinter as tk
from tkinter import filedialog, messagebox
import os

"""Convertit des images en tableaux RGB565 et les enregistre dans un fichier d'en-tête C (.h)."""

def rgb_to_rgb565(r, g, b):
    """Permet de convertir un code RGB vers le format RGB565.
    Args:
        r (int): Composante de rouge (0-255).
        g (int): Composante de vert (0-255).
        b (int): Composante de bleu (0-255).
    Returns:
        int: Valeur RGB565."""
    r = (r >> 3) & 0x1F  # 5 bits for red
    g = (g >> 2) & 0x3F  # 6 bits for green
    b = (b >> 3) & 0x1F  # 5 bits for blue
    return (r << 11) | (g << 5) | b


def image_to_rgb565_array(image_path):
    """Permet de convertir une image vers un tableau de RGB565 sans changer la taille.
    Args:
        image_path (str): Chemin de l'image à convertir.
    Returns:
        (Tableau, Largeur, Hauteur) (tuple): Un tuple contenant le tableau RGB565, la largeur et la hauteur de l'image."""
    img = Image.open(image_path).convert('RGB')
    width, height = img.size
    rgb565_array = np.zeros((height, width), dtype=np.uint16)

    for y in range(height):
        for x in range(width):
            r, g, b = img.getpixel((x, y))
            rgb565_array[y, x] = rgb_to_rgb565(r, g, b)

    return rgb565_array, width, height


def save_arrays_to_header_file(images_dict, filename):
    """Enregistre plusieurs tableaux RGB565 dans un seul fichier .h.
    Args:
        images_dict (dict): Dictionnaire contenant les tableaux d'images.
        filename (str): Nom du fichier de sortie."""
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
    """ Ouvre une fenêtre de dialogue pour sélectionner un dossier et traite toutes les images à l'intérieur."""
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
                messagebox.showwarning("Pas d'images trouvées", "Pas d'images valides trouvées dans le dossier sélectionné.")
        except Exception as e:
            messagebox.showerror("Erreur: ", str(e))


# Interface graphique
root = tk.Tk() 
root.title("Convertisseur d'images RGB vers RGB565")
root.geometry("400x200")

# Bouton pour sélectionner le dossier
button = tk.Button(root, text="Choisissez le dossier", command=select_folder)
button.pack(pady=20)


root.mainloop()
