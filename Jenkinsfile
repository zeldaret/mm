pipeline {
    agent {
        label 'mm'
    }

    stages {
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
                sh 'python3 tools/warnings_count/compare_warnings.py tools/warnings_count/warnings_setup_current.txt tools/warnings_count/warnings_setup_new.txt'
            }
        }
        stage('Build') {
            steps {
                sh 'bash -c "make -j all 2> >(tee tools/warnings_count/warnings_build_new.txt)"'
            }
        }
        stage('Check build warnings') {
            steps {
                sh 'python3 tools/warnings_count/compare_warnings.py tools/warnings_count/warnings_build_current.txt tools/warnings_count/warnings_build_new.txt'
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
    }
    post {
        always {
            cleanWs()
        }
    }
}
