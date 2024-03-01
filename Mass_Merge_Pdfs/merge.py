import PyPDF2
import os

def get_files_in_directory(directory_path):
    # Get the absolute path of the program's directory
    program_directory = os.path.dirname(os.path.abspath(__file__))
    full_directory_path = os.path.join(program_directory, directory_path)

    files = []
    for file_name in os.listdir(full_directory_path):
        file_path = os.path.join(full_directory_path, file_name)
        if os.path.isfile(file_path):
            files.append(file_path)
    return files

def merge_pdfs_with_label(pdf_paths, label, output_directory):
    output_filename = f"{label}.pdf"

    output_directory = os.path.abspath(output_directory)  # Ensure the output directory path is absolute

    if not os.path.exists(output_directory):
        os.makedirs(output_directory)  # Create the output directory if it doesn't exist

    merger = PyPDF2.PdfMerger()

    for path in pdf_paths:
        try:
            with open(path, 'rb') as pdf_file:
                merger.append(pdf_file)
        except PyPDF2.errors.PdfReadError as e:
            print(f"Error reading PDF file: {path}. Skipping file.")

    with open(os.path.join(output_directory, output_filename), 'wb') as output_file:
        merger.write(output_file)

    #print(f"Merged PDFs saved as {output_filename}")

    return output_filename

def move_file_to_done_folder(file_path, done_directory):
    file_name = os.path.basename(file_path)
    destination_path = os.path.join(done_directory, file_name)
    os.rename(file_path, destination_path)
    print(f"Merged file moved to {destination_path}")

def main():
    #dir_name = input("Enter directory name: ")
    #output_dir = input("Enter output directory name: ")
    dir_name = "dir"
    output_dir = "done"
    # Get the absolute path of the program's directory
    program_directory = os.path.dirname(os.path.abspath(__file__))
    input_directory_path = os.path.join(program_directory, dir_name)  # Construct the full input directory path
    output_directory_path = os.path.join(program_directory, output_dir)  # Construct the full output directory path

    files = get_files_in_directory(input_directory_path)
    op = 'approval.pdf'
    merged_files = []

    for file in files:
        name = file[:-4]
        pdf_paths = [file, op]
        label = f"{name}"
        try:
            merged_file = merge_pdfs_with_label(pdf_paths, label, output_directory_path)
            move_file_to_done_folder(merged_file, output_directory_path)
        except PyPDF2.errors.PdfReadError as e:
            print(f"Error merging PDFs for file: {file}. Skipping file.")

if __name__ == "__main__":
    main()
