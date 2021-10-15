pipeline {
    agent {
        label 'mm'
    }

    stages {
        stage('Check formatting') {
            steps {
                echo 'Checking formatting...'
                sh 'bash -c "tools/check_format.sh 2>&1 >(tee tools/check_format.txt)"'
            }
        }
        stage('Copy ROM') {
            steps {
                echo 'Setting up ROM...'
                sh 'cp /usr/local/etc/roms/mm.us.rev1.z64 baserom.mm.us.rev1.z64'
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
                sh 'bash -c "make -j all 2> >(tee tools/warnings_count/warnings_build_new.txt)"'
            }
        }
        stage('Check build warnings') {
            steps {
                sh 'bash -c "./tools/warnings_count/compare_warnings.sh build"'
            }
        }
        stage('Report Progress') {
            when {
                branch 'master'
            }
            steps {
                sh 'mkdir reports'
                sh 'python3 ./tools/progress.py csv >> reports/progress_mm.us.rev1.csv'
                sh 'python3 ./tools/progress.py csv -m >> reports/progress_matching_mm.us.rev1.csv'
                sh 'python3 ./tools/progress.py shield-json > reports/progress_shield_mm.us.rev1.json'
                stash includes: 'reports/*', name: 'reports'
            }
        }
        stage('Update Progress') {
            when {
                branch 'master'
            }
            agent{
                label 'master'
            }
            steps {
                unstash 'reports'
                sh 'cat reports/progress_mm.us.rev1.csv >> /var/www/html/reports/progress_mm.us.rev1.csv'
                sh 'cat reports/progress_matching_mm.us.rev1.csv >> /var/www/html/reports/progress_matching_mm.us.rev1.csv'
                sh 'cat reports/progress_shield_mm.us.rev1.json > /var/www/html/reports/progress_shield_mm.us.rev1.json'
            }
        }
        stage('Summarize problems') {
            steps {
                echo 'Summarizing problems...'
                sh 'cat tools/check_format.txt tools/warnings_count/warnings_setup_new.txt tools/warnings_count/warnings_disasm_new.txt tools/warnings_count/warnings_build_new.txt'
                echo 'No more problems.'
            }
        }
    }
    post {
        always {
            cleanWs()
        }
    }
}
