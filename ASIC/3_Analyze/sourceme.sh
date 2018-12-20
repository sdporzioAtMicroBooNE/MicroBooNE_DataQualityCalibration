run(){
  COLOR="\033[1;33m"
  COLOR="\033[1;33m"
  DEFAULT="\033[0m"
  echo -e "${COLOR}-> ${1}${DEFAULT}";
  eval ${1};
}

run "source /grid/fermiapp/products/uboone/setup_uboone.sh"
run "setup uboonecode v06_26_01 -qe10:prof"
run "setup gallery v1_03_08 -qe10:nu:prof"