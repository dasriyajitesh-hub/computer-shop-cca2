

pipeline {
    agent any

    environment {
        AWS_REGION = 'ap-south-1'
        AWS_ACCOUNT_ID = '906462447728'
        ECR_REPOSITORY = 'comp_rep'
        IMAGE_NAME = "${AWS_ACCOUNT_ID}.dkr.ecr.${AWS_REGION}.amazonaws.com/${ECR_REPOSITORY}"
    }

    stages {
        stage('Checkout') {
            steps {
                echo 'Checking out source code'
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
                    else
                        echo "COMPSHOP.cpp not found"
                        exit 1
                    fi
                    echo "C++ compilation successful"
                '''
            }
        }

        stage('Docker Build') {
            steps {
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
                        aws ecr get-login-password --region "$AWS_REGION" |
                            docker login --username AWS --password-stdin \
                            "${AWS_ACCOUNT_ID}.dkr.ecr.${AWS_REGION}.amazonaws.com"

                        docker push "${IMAGE_NAME}:${BUILD_NUMBER}"
                        docker push "${IMAGE_NAME}:latest"
                    '''
                }
            }
        }

        stage('Deploy to Minikube') {
            steps {
                echo 'Deploying to Minikube'
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
                echo 'Verifying deployment'
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
    }

    post {
        success {
            echo 'Pipeline completed successfully!'
            echo 'Image pushed to Amazon ECR and deployment verified.'
        }

        failure {
            echo 'Pipeline failed. Check the stage error in Console Output.'
        }

        always {
            echo 'Pipeline execution finished.'
        }
    }
}
