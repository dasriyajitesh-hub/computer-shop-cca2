
pipeline {
    agent any

    environment {
        AWS_REGION = 'ap-south-1'
        AWS_ACCOUNT_ID = '906462447728'
        ECR_REPOSITORY = 'comp_rep'
        IMAGE_NAME = "${AWS_ACCOUNT_ID}.dkr.ecr.${AWS_REGION}.amazonaws.com/${ECR_REPOSITORY}"
        AWS_CREDENTIALS_ID = 'aws-ecr-credentials'
    }

    stages {

        stage('Checkout') {
            steps {
                echo 'Checking out source code from GitHub'
                checkout scm
            }
        }

        stage('Build and Test') {
            steps {
                echo 'Building C++ application'

                sh '''
                    set -e

                    if [ -f COMPSHOP.cpp ]; then
                        g++ -std=c++17 -Wall -Wextra COMPSHOP.cpp -o COMPSHOP
                    elif [ -f webserver.cpp ]; then
                        g++ -std=c++17 -Wall -Wextra webserver.cpp -o webserver
                    else
                        echo "ERROR: No supported C++ source file found."
                        exit 1
                    fi

                    echo "C++ compilation successful"
                '''
            }
        }

        stage('Docker Build') {
            steps {
                echo 'Building Docker image'

                sh '''
                    set -e
                    docker build -t ${IMAGE_NAME}:${BUILD_NUMBER} .
                    docker tag ${IMAGE_NAME}:${BUILD_NUMBER} ${IMAGE_NAME}:latest
                '''
            }
        }

        stage('Push Image to Amazon ECR') {
            steps {
                withCredentials([[
                    $class: 'AmazonWebServicesCredentialsBinding',
                    credentialsId: 'aws-ecr-credentials'
                ]]) {
                    sh '''
                        set -e

                        aws ecr get-login-password --region "$AWS_REGION" \
                          | docker login \
                            --username AWS \
                            --password-stdin \
                            "${AWS_ACCOUNT_ID}.dkr.ecr.${AWS_REGION}.amazonaws.com"

                        docker push "${IMAGE_NAME}:${BUILD_NUMBER}"
                        docker push "${IMAGE_NAME}:latest"
                    '''
                }
            }
        }

        
stage('Deploy to Minikube') {
    steps {
        echo 'Deploying application to the existing Minikube cluster'

        sh '''
            set -e

            sudo -u ec2-user /usr/local/bin/minikube status

            sudo -u ec2-user /usr/local/bin/kubectl apply -f k8s/

            sudo -u ec2-user /usr/local/bin/kubectl set image \
              deployment/computer-shop \
              computer-shop="${IMAGE_NAME}:${BUILD_NUMBER}"

            sudo -u ec2-user /usr/local/bin/kubectl rollout status \
              deployment/computer-shop --timeout=180s
        '''
    }
}


        
stage('Verify Application') {
    steps {
        echo 'Verifying Kubernetes deployment'

        sh '''
            set -e

            sudo -u ec2-user /usr/local/bin/kubectl get deployments
            sudo -u ec2-user /usr/local/bin/kubectl get pods -o wide
            sudo -u ec2-user /usr/local/bin/kubectl get services

            sudo -u ec2-user /usr/local/bin/kubectl rollout status \
              deployment/computer-shop --timeout=180s
        '''
    }
}

    post {
        success {
            echo 'CCA2 CI/CD pipeline completed successfully!'
            echo 'Docker image pushed to Amazon ECR.'
            echo 'Kubernetes deployment verified.'
        }

        failure {
            echo 'Pipeline failed. Check the console output for the failing stage.'
        }

        always {
            echo 'Pipeline execution finished.'
        }
    }
}
