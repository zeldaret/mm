pipeline {
    agent any

    stages {
        stage('Copy ROM') {
            steps {
                echo 'Setting up ROM...'
                sh 'cp /usr/local/etc/roms/baserom_mm.z64 baserom.z64'
            }
        }
        stage('Build (qemu-irix)') {
            when {
                branch 'master'
            }
            steps {
                sh 'ORIG_COMPILER=1 make -j init'
            }
        }
        stage('Build (ido-recomp)') {
            when {
                not {
                    branch 'master'
                }
            }
            steps {
                sh 'make -j init'
            }
        }
        stage('Report Progress') {
            when {
                branch 'master'
            }
            steps {
                sh 'python3 ./tools/progress.py csv >> /var/www/html/reports/progress_mm.csv'
                sh 'python3 ./tools/progress.py csv -m >> /var/www/html/reports/progress_mm_matching.csv'
                sh 'python3 ./tools/progress.py shield-json > /var/www/html/reports/progress_mm_shield.json'
            }
        }
    }
    post {
        always {
            cleanWs()
        }
    }
}
