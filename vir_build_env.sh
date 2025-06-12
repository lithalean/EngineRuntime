# Create a virtual environment (recommended)
python3 -m venv vir_build_env
source vir_build_env/bin/activate
pip install requests py7zr

# Then run the build script
##python3 cleanup_repo.py
python3 Jenova.Builder_ARM64.py