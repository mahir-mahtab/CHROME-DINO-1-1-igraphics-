from PIL import Image, ImageOps
import os

def convert_images_to_bmp(input_folder, output_folder, width=None, height=None, transparent_bg=False):
    """
    Converts all image files in a folder to BMP format with optional resizing and transparent background handling.

    Parameters:
        input_folder (str): Path to the input folder containing images.
        output_folder (str): Path to save the output BMP files.
        width (int): Optional. Desired width in pixels.
        height (int): Optional. Desired height in pixels.
        transparent_bg (bool): Optional. If True, set transparent background of PNG images to black.
    """
    if not os.path.exists(output_folder):
        os.makedirs(output_folder, exist_ok=True)
    
    for file_name in os.listdir(input_folder):
        file_path = os.path.join(input_folder, file_name)
        if not os.path.isfile(file_path):
            continue
        
        try:
            # Open the image
            img = Image.open(file_path)
            img_format = img.format
            
            # Handle transparent background for PNG files
            if transparent_bg and img_format == "PNG":
                img = ImageOps.expand(img.convert("RGBA"), border=0, fill=0)
                background = Image.new("RGBA", img.size, (0, 0, 0, 255))  # Black background
                img = Image.alpha_composite(background, img).convert("RGB")
            
            # Resize the image if dimensions are specified
            if width and height:
                img = img.resize((width, height), Image.Resampling.LANCZOS)
            
            # Generate output file path
            base_name, _ = os.path.splitext(file_name)
            output_file = os.path.join(output_folder, f"{base_name}.bmp")
            
            # Save as BMP
            img.save(output_file, format="BMP")
            print(f"Converted: {file_name} -> {output_file}")
        
        except Exception as e:
            print(f"Error processing {file_name}: {e}")

if __name__ == "__main__":
    input_folder = input("Enter the path of the input folder: ").strip()
    output_folder = input("Enter the path of the output folder: ").strip()
    
    # Check if the input folder exists
    if not os.path.exists(input_folder):
        print("Error: The input folder does not exist.")
    else:
        # Ask for resizing options
        resize_choice = input("Do you want to resize the images? (yes/no): ").strip().lower()
        width, height = None, None
        if resize_choice == "yes":
            try:
                width = int(input("Enter the desired width in pixels: ").strip())
                height = int(input("Enter the desired height in pixels: ").strip())
            except ValueError:
                print("Invalid dimensions entered. Resizing will not be applied.")
        
        # Handle PNG transparent background option
        transparent_bg_choice = input("Do you want to replace transparent backgrounds with black? (yes/no): ").strip().lower()
        transparent_bg = transparent_bg_choice == "yes"
        
        # Perform the conversion
        convert_images_to_bmp(input_folder, output_folder, width, height, transparent_bg)
