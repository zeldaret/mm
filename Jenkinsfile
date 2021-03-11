pipeline {
    agent any

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
                sh 'python3 ./tools/progress.py csv >> /var/www/html/reports/progress_mm.us.rev1.csv'
                sh 'python3 ./tools/progress.py csv -m >> /var/www/html/reports/progress_matching_mm.us.rev1.csv'
                sh 'python3 ./tools/progress.py shield-json > /var/www/html/reports/progress_shield_mm.us.rev1.json'
            }
        }
    }
    post {
        always {
            cleanWs()
        }
    }
}
