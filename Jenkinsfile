pipeline {
    agent {
        label 'mm'
    }

    options {
        ansiColor('xterm')
    }

    stages {
        stage('Check formatting') {
            steps {
                echo 'Checking formatting...'
                sh 'bash -c "tools/check_format.sh 2>&1 >(tee tools/check_format.txt)"'
            }
        }
        stage('Check relocs') {
            steps {
                echo 'Checking relocs on spec...'
                sh 'bash -c "tools/reloc_spec_check.sh"'
            }
        }
        stage('Install Python dependencies') {
            steps {
                sh 'bash -c "make -j venv"'
                sh '.venv/bin/python3 -m pip install GitPython' // Progress script from jenkins requires GitPython
            }
        }
        stage('Copy ROM') {
            steps {
                echo 'Setting up ROM...'
                sh 'cp /usr/local/etc/roms/mm.us.rev1.z64 baseroms/n64-us/baserom.z64'
            }
        }
        stage('Setup') {
            steps {
                sh 'bash -c "make -j setup 2> >(tee tools/warnings_count/warnings_setup_new.txt)"'
            }
        }
        stage('Check setup warnings') {
            steps {
                sh 'bash -c "./tools/warnings_count/compare_warnings.sh setup"'
            }
        }
        stage('Assets') {
            steps {
                sh 'bash -c "make -j assets 2> >(tee tools/warnings_count/warnings_assets_new.txt)"'
            }
        }
        stage('Check assets warnings') {
            steps {
                sh 'bash -c "./tools/warnings_count/compare_warnings.sh assets"'
            }
        }
        stage('Disasm') {
            steps {
                sh 'bash -c "make -j disasm 2> >(tee tools/warnings_count/warnings_disasm_new.txt)"'
            }
        }
        stage('Check disasm warnings') {
            steps {
                sh 'bash -c "./tools/warnings_count/compare_warnings.sh disasm"'
            }
        }
        stage('Build') {
            steps {
                sh 'bash -c "make -j rom 2> >(tee tools/warnings_count/warnings_build_new.txt)"'
            }
        }
        stage('Check build warnings') {
            steps {
                sh 'bash -c "./tools/warnings_count/compare_warnings.sh build"'
            }
        }
        stage('Compress') {
            steps {
                sh 'bash -c "make -j compress 2> >(tee tools/warnings_count/warnings_compress_new.txt)"'
            }
        }
        stage('Check compress warnings') {
            steps {
                sh 'bash -c "./tools/warnings_count/compare_warnings.sh compress"'
            }
        }
        stage('Report Progress') {
            when {
                branch 'main'
            }
            steps {
                sh 'mkdir reports'
                sh '.venv/bin/python3 ./tools/progress.py csv >> reports/progress-mm-nonmatching.csv'
                sh '.venv/bin/python3 ./tools/progress.py csv -m >> reports/progress-mm-matching.csv'
                sh '.venv/bin/python3 ./tools/progress.py shield-json > reports/progress-mm-shield.json'
                stash includes: 'reports/*', name: 'reports'
            }
        }
        stage('Update Progress') {
            when {
                branch 'main'
            }
            agent{
                label 'zeldaret_website'
            }
            steps {
                unstash 'reports'
                sh 'cat reports/progress-mm-nonmatching.csv >> /var/www/zelda64.dev/assets/csv/progress-mm-nonmatching.csv'
                sh 'cat reports/progress-mm-matching.csv >> /var/www/zelda64.dev/assets/csv/progress-mm-matching.csv'
                sh 'cat reports/progress-mm-shield.json > /var/www/zelda64.dev/assets/csv/progress-mm-shield.json'
            }
        }
    }
    post {
        failure {
            sh 'cat tools/check_format.txt tools/warnings_count/warnings_setup_new.txt tools/warnings_count/warnings_disasm_new.txt tools/warnings_count/warnings_build_new.txt'
        }
        always {
            cleanWs()
        }
    }
}
