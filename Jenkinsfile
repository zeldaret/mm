pipeline {
    agent {
        label 'mm'
    }

    stages {
        stage('Copy ROM') {
            steps {
                echo 'Setting up ROM...'
                sh 'cp /usr/local/etc/roms/mm.us.rev1.z64 baserom.z64'
            }
        }
        stage('Build') {
            steps {
                sh 'make -j init'
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
            agent{
                label 'master'
            }
            when {
                branch 'master'
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
