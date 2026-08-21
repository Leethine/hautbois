#!/bin/sh

if [[ "${1}" == "--help" ]] || [[ "${1}" == "-h" ]]; then
  echo "Usage: ${0} src.cpp [target.bin]"
  exit 0
fi

src_file="${1}"
if [[ -z "${src_file}" ]]; then
  src_file="__PREPROCESSED__.cpp"
fi

target_file="${2}"
if [[ -z "${target_file}" ]]; then
  target_file="__BIN__"
fi

linked_lib_path=""

###__TEXT_REPLACE_TAG__###

# Check
if [[ -z "${src_file}" ]] || [[ ! -f "${src_file}" ]]; then
  echo "No valid Source provided: ${src_file}"
  exit 1
fi

if [[ -d "${target_file}" ]]; then
  echo "Cannot override dest file: ${target_file}"
  exit 1
fi

g++ ${linked_lib_path} -std=c++17 "${src_file}" -lm -lasound -lstk -lHb -o "${target_file}" && ./${target_file}
