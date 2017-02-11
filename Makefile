all:
	ansible-playbook -i ansible_hosts copy_and_build.yml
