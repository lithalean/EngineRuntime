#!/usr/bin/env python3
"""
Repository Cleanup Script for EngineRuntime
Removes unnecessary files while keeping essential development files.
"""

import os
import shutil
import fnmatch
import argparse
from pathlib import Path

class RepoCleanup:
	def __init__(self, repo_path):
		self.repo_path = Path(repo_path).resolve()
		self.files_to_remove = []
		self.dirs_to_remove = []
		self.total_size_saved = 0
		
		# Files to definitely remove (by extension)
		self.remove_extensions = {
			# Binary files
			'.dll', '.so', '.dylib', '.lib', '.a', '.exe', '.bin',
			# Object files
			'.o', '.obj', '.pdb', '.ilk', '.exp',
			# Archive files
			'.zip', '.tar', '.gz', '.7z', '.rar',
			# Cache files
			'.cache', '.tmp', '.temp',
			# IDE files (some)
			'.user', '.suo', '.ncb', '.aps', '.plg',
			# Backup files
			'.bak', '.backup', '.orig', '~'
		}
		
		# Directories to remove
		self.remove_dirs = {
			'build', 'Build', 'BUILD',
			'bin', 'Bin', 'BIN',
			'lib', 'Lib', 'LIB',
			'obj', 'Obj', 'OBJ',
			'Debug', 'Release',
			'Win32',
			'.vs', '.vscode/ipch',
			'__pycache__',
			'node_modules',
			'target', 'dist',
			'CMakeFiles',
			'.idea'
		}
		
		# Architecture directories to remove only in specific contexts
		self.conditional_remove_dirs = {
			'x64': ['build/', 'Build/', 'bin/', 'Bin/', 'lib/', 'Lib/', 'out/', 'cmake-build-'],
			'x86': ['build/', 'Build/', 'bin/', 'Bin/', 'lib/', 'Lib/', 'out/', 'cmake-build-'],
			'arm64': ['build/', 'Build/', 'bin/', 'Bin/', 'lib/', 'Lib/', 'out/', 'cmake-build-'],
			'aarch64': ['build/', 'Build/', 'bin/', 'Bin/', 'lib/', 'Lib/', 'out/', 'cmake-build-']
		}
		
		# Files to definitely keep (by extension)
		self.keep_extensions = {
			# Source code
			'.cpp', '.hpp', '.h', '.c', '.cc', '.cxx',
			# Build system
			'.cmake', '.py', '.json', '.toml', '.ini', '.cfg',
			# Documentation
			'.md', '.txt', '.rst', '.pdf',
			# Configuration
			'.gitignore', '.gitmodules', '.gitattributes',
			# Godot files
			'.gdextension', '.gd', '.cs',
			# Scripts
			'.sh', '.bat', '.ps1'
		}
		
		# File patterns to keep (even if extension might suggest removal)
		self.keep_patterns = [
			'README*',
			'LICENSE*',
			'CHANGELOG*',
			'CMakeLists.txt',
			'Makefile*',
			'SConstruct*',
			'SConscript*',
			'*.Builder*',
			'Jenova.*',
			'requirements.txt',
			'package.json',
			'Cargo.toml'
		]
		
		# Directories to always keep
		self.keep_dirs = {
			'.git',
			'Source', 'src', 'source',
			'Include', 'include', 'inc',
			'Headers', 'headers',
			'Documentation', 'docs', 'doc',
			'Examples', 'examples', 'sample',
			'Scripts', 'scripts',
			'Tools', 'tools',
			'Tests', 'test', 'testing'
		}

	def should_keep_file(self, file_path):
		"""Determine if a file should be kept."""
		file_name = file_path.name
		file_ext = file_path.suffix.lower()
		
		# Always keep files matching keep patterns
		for pattern in self.keep_patterns:
			if fnmatch.fnmatch(file_name, pattern):
				return True
		
		# Keep files with extensions we want to preserve
		if file_ext in self.keep_extensions:
			return True
			
		# Remove files with extensions we don't want
		if file_ext in self.remove_extensions:
			return False
			
		# Keep files without extensions (might be scripts or config)
		if not file_ext:
			return True
			
		# Default: ask user for unknown extensions
		return None

	def should_keep_dir(self, dir_path):
		"""Determine if a directory should be kept."""
		dir_name = dir_path.name
		
		# Always keep certain directories
		if dir_name in self.keep_dirs:
			return True
			
		# Remove known build/cache directories
		if dir_name in self.remove_dirs:
			return False
			
		# Handle architecture directories conditionally
		if dir_name in self.conditional_remove_dirs:
			parent_path = str(dir_path.parent).lower()
			remove_contexts = self.conditional_remove_dirs[dir_name]
			
			# Only remove arch dirs if they're inside build/output directories
			for context in remove_contexts:
				if context.rstrip('/') in parent_path:
					return False
			
			# Keep arch directories in source code contexts (like src/asmjit/x86/)
			return True
			
		# Keep other directories by default
		return True

	def get_file_size(self, file_path):
		"""Get file size in bytes."""
		try:
			return file_path.stat().st_size
		except (OSError, FileNotFoundError):
			return 0

	def format_size(self, size_bytes):
		"""Format file size in human readable format."""
		for unit in ['B', 'KB', 'MB', 'GB']:
			if size_bytes < 1024.0:
				return f"{size_bytes:.1f} {unit}"
			size_bytes /= 1024.0
		return f"{size_bytes:.1f} TB"

	def scan_repository(self):
		"""Scan repository and identify files/directories to remove."""
		print(f"Scanning repository: {self.repo_path}")
		
		unknown_extensions = set()
		
		for root, dirs, files in os.walk(self.repo_path):
			root_path = Path(root)
			
			# Skip .git directory
			if '.git' in root_path.parts:
				continue
				
			# Check directories
			dirs_to_remove_from_walk = []
			for dir_name in dirs[:]:  # Create a copy to modify during iteration
				dir_path = root_path / dir_name
				if not self.should_keep_dir(dir_path):
					self.dirs_to_remove.append(dir_path)
					dirs_to_remove_from_walk.append(dir_name)
					
			# Remove directories from walk to avoid scanning their contents
			for dir_name in dirs_to_remove_from_walk:
				dirs.remove(dir_name)
			
			# Check files
			for file_name in files:
				file_path = root_path / file_name
				keep_decision = self.should_keep_file(file_path)
				
				if keep_decision is False:
					file_size = self.get_file_size(file_path)
					self.files_to_remove.append((file_path, file_size))
					self.total_size_saved += file_size
				elif keep_decision is None:
					# Unknown extension - collect for user review
					unknown_extensions.add(file_path.suffix.lower())
		
		return unknown_extensions

	def preview_cleanup(self):
		"""Show what will be removed without actually removing it."""
		print("\n" + "="*60)
		print("CLEANUP PREVIEW")
		print("="*60)
		
		if self.dirs_to_remove:
			print(f"\nDirectories to remove ({len(self.dirs_to_remove)}):")
			for dir_path in sorted(self.dirs_to_remove):
				rel_path = dir_path.relative_to(self.repo_path)
				print(f"  📁 {rel_path}")
		
		if self.files_to_remove:
			print(f"\nFiles to remove ({len(self.files_to_remove)}):")
			for file_path, size in sorted(self.files_to_remove):
				rel_path = file_path.relative_to(self.repo_path)
				print(f"  📄 {rel_path} ({self.format_size(size)})")
		
		print(f"\nTotal space to be freed: {self.format_size(self.total_size_saved)}")

	def execute_cleanup(self, dry_run=True):
		"""Execute the cleanup operation."""
		if dry_run:
			print("\n🔍 DRY RUN - No files will actually be deleted")
			self.preview_cleanup()
			return
		
		print("\n🗑️  EXECUTING CLEANUP...")
		
		removed_files = 0
		removed_dirs = 0
		actual_size_saved = 0
		
		# Remove files
		for file_path, estimated_size in self.files_to_remove:
			try:
				if file_path.exists():
					actual_size = self.get_file_size(file_path)
					file_path.unlink()
					removed_files += 1
					actual_size_saved += actual_size
					print(f"  ✅ Removed: {file_path.relative_to(self.repo_path)}")
			except Exception as e:
				print(f"  ❌ Error removing {file_path.relative_to(self.repo_path)}: {e}")
		
		# Remove directories
		for dir_path in self.dirs_to_remove:
			try:
				if dir_path.exists():
					shutil.rmtree(dir_path)
					removed_dirs += 1
					print(f"  ✅ Removed directory: {dir_path.relative_to(self.repo_path)}")
			except Exception as e:
				print(f"  ❌ Error removing {dir_path.relative_to(self.repo_path)}: {e}")
		
		print(f"\n✨ Cleanup complete!")
		print(f"   📄 Files removed: {removed_files}")
		print(f"   📁 Directories removed: {removed_dirs}")
		print(f"   💾 Space freed: {self.format_size(actual_size_saved)}")

	def interactive_review(self, unknown_extensions):
		"""Allow user to review unknown file extensions."""
		if not unknown_extensions:
			return
			
		print(f"\n❓ Found {len(unknown_extensions)} unknown file extensions:")
		for ext in sorted(unknown_extensions):
			if not ext:
				ext = "(no extension)"
			print(f"   {ext}")
		
		print("\nReview files with these extensions manually if needed.")
		print("The script will keep them by default to be safe.")

def main():
	parser = argparse.ArgumentParser(
		description="Clean up EngineRuntime repository by removing unnecessary files"
	)
	parser.add_argument(
		"repo_path", 
		nargs="?", 
		default=".", 
		help="Path to repository (default: current directory)"
	)
	parser.add_argument(
		"--execute", 
		action="store_true", 
		help="Actually remove files (default is dry-run)"
	)
	parser.add_argument(
		"--force", 
		action="store_true", 
		help="Skip confirmation prompt"
	)
	
	args = parser.parse_args()
	
	# Validate repository path
	repo_path = Path(args.repo_path).resolve()
	if not repo_path.exists():
		print(f"❌ Error: Repository path does not exist: {repo_path}")
		return 1
	
	if not (repo_path / ".git").exists():
		print(f"⚠️  Warning: {repo_path} doesn't appear to be a git repository")
		if not args.force:
			response = input("Continue anyway? (y/N): ")
			if response.lower() != 'y':
				return 0
	
	# Initialize cleanup
	cleanup = RepoCleanup(repo_path)
	
	# Scan repository
	unknown_extensions = cleanup.scan_repository()
	
	# Show preview
	cleanup.preview_cleanup()
	
	# Review unknown extensions
	cleanup.interactive_review(unknown_extensions)
	
	# Execute cleanup
	if args.execute:
		if not args.force:
			print(f"\n⚠️  This will permanently delete {len(cleanup.files_to_remove)} files and {len(cleanup.dirs_to_remove)} directories!")
			response = input("Are you sure you want to continue? (y/N): ")
			if response.lower() != 'y':
				print("Cleanup cancelled.")
				return 0
		
		cleanup.execute_cleanup(dry_run=False)
	else:
		print(f"\n💡 This was a dry run. Use --execute to actually remove files.")
		print(f"💡 Example: python {parser.prog} {args.repo_path} --execute")
	
	return 0

if __name__ == "__main__":
	exit(main())